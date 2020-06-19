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