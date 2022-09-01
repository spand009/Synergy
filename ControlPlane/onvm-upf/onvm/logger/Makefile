logger.h: liblogger.a ;

liblogger.a:
	go build -o liblogger.a -buildmode=c-archive logger.go
	mv liblogger.h logger.h

clean:
	rm *.a *.h 
