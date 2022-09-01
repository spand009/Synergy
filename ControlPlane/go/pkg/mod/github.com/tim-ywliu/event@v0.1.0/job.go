package event

// job represents events. When a new event is dispatched, it
// gets tuned into a job and put into `Dispatcher.jobs` channel.
type job struct {
	eventName Name
	eventType interface{}
}
