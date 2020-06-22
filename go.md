## Go

### Server

```golang
package main

import "fmt"
import "net/http"

func hello(w http.ResponseWriter, req *http.Request) {
  fmt.Fprintf(w, "world\n")
}

func main() {
  http.HandleFunc("/hello", hello)
  http.ListenAndServe(":8090", nil)
}
```

### Stdin

```golang
package main

import (
  "fmt"
  "os"
  "bufio"
  "log"
)

func main() {
  scanner := bufio.NewScanner(os.Stdin)
  for scanner.Scan() {
    fmt.Println(scanner.Text())
  }

  if err := scanner.Err(); err != nil {
    log.Println(err)
  }
}
```

### Gorutines + channels
```golang
package main

import "fmt"
import "net/http"

type Hub struct {
   color string
   message chan string
}

func newHub() *Hub {
  return &Hub{
    color: "white",
    message: make(chan string),
  }
}

func (h *Hub) run() {
  for {
    select {
      case msg:= <-h.message:
        h.color = msg
    }
  }
}

func main() {
  hub := newHub()
  go hub.run()

  http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintf(w, hub.color);
  })

  http.HandleFunc("/change", func(w http.ResponseWriter, r *http.Request) {
    hub.message <- "red";
    fmt.Fprintf(w, "OK\n");
  })

  http.ListenAndServe(":9090", nil)
}
```
