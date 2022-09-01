package event

// All custom event listeners must satisfy this interface.
type Listener interface {
	Listen(event interface{})
}
