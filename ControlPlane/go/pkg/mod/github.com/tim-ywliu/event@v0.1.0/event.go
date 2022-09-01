package event

// All custom events names must be of this type.
type Name string

// All custom event types must satisfy this interface.
type Event interface {
	Handle()
}
