---
layout: page
title: Serving Static Files
tagline: Mean Stack
nav: true
category: mean
tags: mean, express, static files, http, get, html
---

Serve a static page from the root of our server.

- We'll create a new folder 'public' at the same level as our index.js.
- Then we will create a file named 'index.html'

##### Ls #####
    backend/
        public/            <!-- new folder: /public -->
            index.html     <!-- new file: /public/index.html -->
        node_modules
        package.json
        index.js

##### index.html #####
```html
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
    </head>
    <body>
        <h1>Hello World!</h1>
    </body>
</html>
```

#### index.js ####

We edit our server to serve the files at the root of our server.

```JavaScript
var express = require('express');

var app = express();

app.use(express.static(__dirname + '/public'));

app.listen(3000);
```

#### Test ####
    $ node index.js
    $ curl localhost:3000
    <!DOCTYPE html>
    <html>
        <head>
            <meta charset="utf-8">
        </head>
        <body>
            <h1>Hello World!</h1>
        </body>
    </html>

#### Browser test ####

We can also test this in our browser.

![Static file displayed]({{ site.url }}/assets/2016-05-21-serving-static-files-01.png)
