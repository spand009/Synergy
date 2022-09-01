# event
A go package for event listener and dispatcher with channel.

**Original Place: [event-listener-and-dispatcher-example-with-golang](http://www.inanzzz.com/index.php/post/2qdl/event-listener-and-dispatcher-example-with-golang)**

## Features

- One dispatcher can register many listeners.

- One dispatcher can register many events for a specific given listener.

- One dispatcher can dispatch many events.

- One listener can listen on many events.

- One event can be linked to one event type.

- The dispatcher prevents registering duplicated events.

- The dispatcher prevents dispatching non-registered events.

## Usage Sample

### Create your own events

user/created.go:

```go
package user
 
import (
	"log"
	"time"
 
	"github.com/tim-ywliu/event"
)
 
const Created event.Name = "user.created"
 
type CreatedEvent struct {
	Time time.Time
	ID   string
}
 
func (e CreatedEvent) Handle() {
	log.Printf("creating: %+v\n", e)
}
```

### Write your event listener

user/listener.go:

```go
package user
 
import (
	"log"
)
 
type UserListener struct{}
 
func (u UserListener) Listen(event interface{}) {
	switch event := event.(type) {
	case CreatedEvent:
		event.Handle()
	default:
		log.Printf("registered an invalid user event: %T\n", event)
	}
}
```

### Write your event dispatch method

user/dispatcher.go:

```go
package user

var userDispatcher *event.Dispatcher

import (
	"log"
	"time"

	"github.com/tim-ywliu/event"
)

func RegisterUserDispatcher() error {
	userDispatcher = event.NewDispatcher()
	if err := userDispatcher.Register(UserListener{}, Created); err != nil {
		return err
	}
	return nil
}

func DispatchUserCreatedEvent() {
	err := userDispatcher.Dispatch(Created, CreatedEvent{
		Time: time.Now().UTC(),
		ID:   "111",
	})
	if err != nil {
		log.Println(err)
	}
}
```
