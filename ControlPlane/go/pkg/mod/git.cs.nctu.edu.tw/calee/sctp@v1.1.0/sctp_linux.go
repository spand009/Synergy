// +build linux,!386
// Copyright 2019 Wataru Ishida. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
// implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package sctp

import (
	"io"
	"net"
	"sync/atomic"
	"syscall"
	"unsafe"
)

func setsockopt(fd int, optname, optval, optlen uintptr) (uintptr, uintptr, error) {
	// FIXME: syscall.SYS_SETSOCKOPT is undefined on 386
	r0, r1, errno := syscall.Syscall6(syscall.SYS_SETSOCKOPT,
		uintptr(fd),
		SOL_SCTP,
		optname,
		optval,
		optlen,
		0)
	if errno != 0 {
		return r0, r1, errno
	}
	return r0, r1, nil
}

func getsockopt(fd int, optname, optval, optlen uintptr) (uintptr, uintptr, error) {
	// FIXME: syscall.SYS_GETSOCKOPT is undefined on 386
	r0, r1, errno := syscall.Syscall6(syscall.SYS_GETSOCKOPT,
		uintptr(fd),
		SOL_SCTP,
		optname,
		optval,
		optlen,
		0)
	if errno != 0 {
		return r0, r1, errno
	}
	return r0, r1, nil
}

type rawConn struct {
	sockfd int
}

func (r rawConn) Control(f func(fd uintptr)) error {
	f(uintptr(r.sockfd))
	return nil
}

func (r rawConn) Read(f func(fd uintptr) (done bool)) error {
	panic("not implemented")
}

func (r rawConn) Write(f func(fd uintptr) (done bool)) error {
	panic("not implemented")
}

func (c *SCTPConn) SCTPWrite(b []byte, info *SndRcvInfo) (int, error) {
	var cbuf []byte
	if info != nil {
		cmsgBuf := toBuf(info)
		hdr := &syscall.Cmsghdr{
			Level: syscall.IPPROTO_SCTP,
			Type:  SCTP_CMSG_SNDRCV,
		}

		// bitwidth of hdr.Len is platform-specific,
		// so we use hdr.SetLen() rather than directly setting hdr.Len
		hdr.SetLen(syscall.CmsgSpace(len(cmsgBuf)))
		cbuf = append(toBuf(hdr), cmsgBuf...)
	}
	return syscall.SendmsgN(c.fd(), b, cbuf, nil, 0)
}

func parseSndRcvInfo(b []byte) (*SndRcvInfo, error) {
	msgs, err := syscall.ParseSocketControlMessage(b)
	if err != nil {
		return nil, err
	}
	for _, m := range msgs {
		if m.Header.Level == syscall.IPPROTO_SCTP {
			switch m.Header.Type {
			case SCTP_CMSG_SNDRCV:
				return (*SndRcvInfo)(unsafe.Pointer(&m.Data[0])), nil
			}
		}
	}
	return nil, nil
}

func parseNotification(b []byte) Notification {
	snType := SCTPNotificationType(nativeEndian.Uint16(b[:2]))

	switch snType {
	case SCTP_SHUTDOWN_EVENT:
		notification := SCTPShutdownEvent{
			sseType:    nativeEndian.Uint16(b[:2]),
			sseFlags:   nativeEndian.Uint16(b[2:4]),
			sseLength:  nativeEndian.Uint32(b[4:8]),
			sseAssocID: SCTPAssocID(nativeEndian.Uint32(b[8:])),
		}
		return &notification
	case SCTP_ASSOC_CHANGE:
		notification := SCTPAssocChangeEvent{
			sacType:            nativeEndian.Uint16(b[:2]),
			sacFlags:           nativeEndian.Uint16(b[2:4]),
			sacLength:          nativeEndian.Uint32(b[4:8]),
			sacState:           SCTPState(nativeEndian.Uint16(b[8:10])),
			sacError:           nativeEndian.Uint16(b[10:12]),
			sacOutboundStreams: nativeEndian.Uint16(b[12:14]),
			sacInboundStreams:  nativeEndian.Uint16(b[14:16]),
			sacAssocID:         SCTPAssocID(nativeEndian.Uint32(b[16:20])),
			sacInfo:            b[20:],
		}
		return &notification
	default:
		return nil
	}
}

// SCTPRead use syscall.Recvmsg to receive SCTP message and return sctp sndrcvinfo/notification if need
func (c *SCTPConn) SCTPRead(b []byte) (int, *SndRcvInfo, Notification, error) {
	oob := make([]byte, 254)
	n, oobn, recvflags, _, err := syscall.Recvmsg(c.fd(), b, oob, 0)
	if err != nil {
		return n, nil, nil, err
	}

	if n == 0 && oobn == 0 {
		return 0, nil, nil, io.EOF
	}

	if recvflags&MSG_NOTIFICATION > 0 {
		notification := parseNotification(b[:n])
		return n, nil, notification, nil
	} else {
		var info *SndRcvInfo
		if oobn > 0 {
			info, err = parseSndRcvInfo(oob[:oobn])
		}
		return n, info, nil, err
	}
}

func (c *SCTPConn) Close() error {
	if c != nil {
		fd := atomic.SwapInt32(&c._fd, -1)
		if fd > 0 {
			info := &SndRcvInfo{
				Flags: SCTP_EOF,
			}
			c.SCTPWrite(nil, info)
			syscall.Shutdown(int(fd), syscall.SHUT_RDWR)
			return syscall.Close(int(fd))
		}
	}
	return syscall.EBADF
}

func (c *SCTPConn) SetWriteBuffer(bytes int) error {
	return syscall.SetsockoptInt(c.fd(), syscall.SOL_SOCKET, syscall.SO_SNDBUF, bytes)
}

func (c *SCTPConn) GetWriteBuffer() (int, error) {
	return syscall.GetsockoptInt(c.fd(), syscall.SOL_SOCKET, syscall.SO_SNDBUF)
}

func (c *SCTPConn) SetReadBuffer(bytes int) error {
	return syscall.SetsockoptInt(c.fd(), syscall.SOL_SOCKET, syscall.SO_RCVBUF, bytes)
}

func (c *SCTPConn) GetReadBuffer() (int, error) {
	return syscall.GetsockoptInt(c.fd(), syscall.SOL_SOCKET, syscall.SO_RCVBUF)
}

func (c *SCTPConn) SetWriteTimeout(tv syscall.Timeval) error {
	return syscall.SetsockoptTimeval(c.fd(), syscall.SOL_SOCKET, syscall.SO_SNDTIMEO, &tv)
}

func (c *SCTPConn) SetReadTimeout(tv syscall.Timeval) error {
	return syscall.SetsockoptTimeval(c.fd(), syscall.SOL_SOCKET, syscall.SO_RCVTIMEO, &tv)
}

func (c *SCTPConn) SetNonBlock(nonBlock bool) error {
	return syscall.SetNonblock(c.fd(), nonBlock)
}

func (c *SCTPConn) GetRtoInfo() (*RtoInfo, error) {
	return getRtoInfo(c.fd())
}

func (c *SCTPConn) SetRtoInfo(rtoInfo RtoInfo) error {
	return setRtoInfo(c.fd(), rtoInfo)
}

func (c *SCTPConn) GetAssocInfo() (*AssocInfo, error) {
	return getAssocInfo(c.fd())
}

func (c *SCTPConn) SetAssocInfo(info AssocInfo) error {
	return setAssocInfo(c.fd(), info)
}

// ListenSCTP - start listener on specified address/port
func ListenSCTP(net string, laddr *SCTPAddr) (*SCTPListener, error) {
	return ListenSCTPExt(net, laddr, InitMsg{NumOstreams: SCTP_MAX_STREAM}, nil, nil)
}

// ListenSCTPExt - start listener on specified address/port with given SCTP options
func ListenSCTPExt(network string, laddr *SCTPAddr, options InitMsg, rtoInfo *RtoInfo, assocInfo *AssocInfo) (*SCTPListener, error) {
	return listenSCTPExtConfig(network, laddr, options, rtoInfo, assocInfo, nil)
}

// listenSCTPExtConfig - start listener on specified address/port with given SCTP options and socket configuration
func listenSCTPExtConfig(network string, laddr *SCTPAddr, options InitMsg, rtoInfo *RtoInfo, assocInfo *AssocInfo, control func(network, address string, c syscall.RawConn) error) (*SCTPListener, error) {
	af, ipv6only := favoriteAddrFamily(network, laddr, nil, "listen")
	sock, err := syscall.Socket(
		af,
		syscall.SOCK_STREAM|syscall.SOCK_NONBLOCK|syscall.SOCK_CLOEXEC,
		syscall.IPPROTO_SCTP,
	)
	if err != nil {
		return nil, err
	}

	// close socket on error
	defer func() {
		if err != nil {
			syscall.Close(sock)
		}
	}()
	if err = setDefaultSockopts(sock, af, ipv6only); err != nil {
		return nil, err
	}

	// enable REUSEADDR option
	if err = syscall.SetsockoptInt(sock, syscall.SOL_SOCKET, syscall.SO_REUSEADDR, 1); err != nil {
		return nil, err
	}

	if control != nil {
		rc := rawConn{sockfd: sock}
		if err = control(network, laddr.String(), rc); err != nil {
			return nil, err
		}
	}

	//RTO
	if rtoInfo != nil {
		err = setRtoInfo(sock, *rtoInfo)
		if err != nil {
			return nil, err
		}
	}

	// set default association parameters (RFC 6458 8.1.2)
	if assocInfo != nil {
		err = setAssocInfo(sock, *assocInfo)
		if err != nil {
			return nil, err
		}
	}

	err = setInitOpts(sock, options)
	if err != nil {
		return nil, err
	}

	if laddr != nil {
		// If IP address and/or port was not provided so far, let's use the unspecified IPv4 or IPv6 address
		if len(laddr.IPAddrs) == 0 {
			if af == syscall.AF_INET {
				laddr.IPAddrs = append(laddr.IPAddrs, net.IPAddr{IP: net.IPv4zero})
			} else if af == syscall.AF_INET6 {
				laddr.IPAddrs = append(laddr.IPAddrs, net.IPAddr{IP: net.IPv6zero})
			}
		}
		err := SCTPBind(sock, laddr, SCTP_BINDX_ADD_ADDR)
		if err != nil {
			return nil, err
		}
	}
	err = syscall.Listen(sock, syscall.SOMAXCONN)
	if err != nil {
		return nil, err
	}

	// epoll will be used in Accept() to avoid busy waiting because of non-blocking socket
	epfd, err := createEpollForSock(sock)
	if err != nil {
		return nil, err
	}

	return &SCTPListener{
		fd:   sock,
		epfd: epfd,
	}, nil
}

// createEpollForSock - create an epoll for sock; return an epoll fd if no error
func createEpollForSock(sock int) (int, error) {
	epfd, err := syscall.EpollCreate1(syscall.EPOLL_CLOEXEC)
	if err != nil {
		return -1, err
	}

	// close epfd on error
	defer func() {
		if err != nil {
			syscall.Close(epfd)
		}
	}()

	event := syscall.EpollEvent{
		Events: syscall.EPOLLIN,
		Fd:     int32(sock),
	}
	err = syscall.EpollCtl(epfd, syscall.EPOLL_CTL_ADD, sock, &event)
	if err != nil {
		return -1, err
	}
	return epfd, nil
}

// AcceptSCTP waits for and returns the next SCTP connection to the listener.
// it will use EpollWait to wait for a incoming connection then call syscall.Accept4 to accept
func (ln *SCTPListener) AcceptSCTP() (*SCTPConn, error) {
	var events [1]syscall.EpollEvent
	n, err := syscall.EpollWait(ln.epfd, events[:], -1)
	if err != nil {
		return nil, err
	}

	if n == 0 {
		return nil, err
	}

	if events[0].Fd == int32(ln.fd) {
		fd, _, err := syscall.Accept4(ln.fd, 0)
		return NewSCTPConn(fd, nil), err
	} else {
		return nil, err
	}
}

// Accept waits for and returns the next connection connection to the listener.
func (ln *SCTPListener) Accept() (net.Conn, error) {
	return ln.AcceptSCTP()
}

func (ln *SCTPListener) Close() error {
	syscall.Shutdown(ln.fd, syscall.SHUT_RDWR)
	syscall.Close(ln.epfd)
	return syscall.Close(ln.fd)
}

// DialSCTP - bind socket to laddr (if given) and connect to raddr
func DialSCTP(net string, laddr, raddr *SCTPAddr) (*SCTPConn, error) {
	return DialSCTPExt(net, laddr, raddr, InitMsg{NumOstreams: SCTP_MAX_STREAM}, nil, nil)
}

// DialSCTPExt - same as DialSCTP but with given SCTP options
func DialSCTPExt(network string, laddr, raddr *SCTPAddr, options InitMsg, rtoInfo *RtoInfo, assocInfo *AssocInfo) (*SCTPConn, error) {
	return dialSCTPExtConfig(network, laddr, raddr, options, rtoInfo, assocInfo, nil)
}

// dialSCTPExtConfig - same as DialSCTP but with given SCTP options and socket configuration
func dialSCTPExtConfig(network string, laddr, raddr *SCTPAddr, options InitMsg, rtoInfo *RtoInfo, assocInfo *AssocInfo, control func(network, address string, c syscall.RawConn) error) (*SCTPConn, error) {
	af, ipv6only := favoriteAddrFamily(network, laddr, raddr, "dial")
	sock, err := syscall.Socket(
		af,
		syscall.SOCK_STREAM,
		syscall.IPPROTO_SCTP,
	)
	if err != nil {
		return nil, err
	}

	// close socket on error
	defer func() {
		if err != nil {
			syscall.Close(sock)
		}
	}()
	if err = setDefaultSockopts(sock, af, ipv6only); err != nil {
		return nil, err
	}
	if control != nil {
		rc := rawConn{sockfd: sock}
		if err = control(network, laddr.String(), rc); err != nil {
			return nil, err
		}
	}

	//RTO
	if rtoInfo != nil {
		err = setRtoInfo(sock, *rtoInfo)
		if err != nil {
			return nil, err
		}
	}

	// AssocInfo
	if assocInfo != nil {
		err = setAssocInfo(sock, *assocInfo)
		if err != nil {
			return nil, err
		}
	}

	err = setInitOpts(sock, options)
	if err != nil {
		return nil, err
	}
	if laddr != nil {
		// If IP address and/or port was not provided so far, let's use the unspecified IPv4 or IPv6 address
		if len(laddr.IPAddrs) == 0 {
			if af == syscall.AF_INET {
				laddr.IPAddrs = append(laddr.IPAddrs, net.IPAddr{IP: net.IPv4zero})
			} else if af == syscall.AF_INET6 {
				laddr.IPAddrs = append(laddr.IPAddrs, net.IPAddr{IP: net.IPv6zero})
			}
		}
		err := SCTPBind(sock, laddr, SCTP_BINDX_ADD_ADDR)
		if err != nil {
			return nil, err
		}
	}
	_, err = SCTPConnect(sock, raddr)
	if err != nil {
		return nil, err
	}
	return NewSCTPConn(sock, nil), nil
}
