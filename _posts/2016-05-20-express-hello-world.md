---
layout: page
title: Express Hello World
tagline: Mean Stack
nav: true
category: mean
tags: mean, express, hello world, http, get, curl
comments: false
---

Basic Express app to render a hello world.

#### Init ####
```Bash
$ mkdir backend && cd backend
$ npm init
$ npm install --save express
$ npm install
$ touch index.js
```

##### Ls #####
    backend/
        node_modules
        package.json
        index.js

#### index.js ####
```JavaScript
var express = require('express');

var app = express();

app.get('/', function(req, res){
    res.send('Hello World!');
});

app.listen(3000);
```

#### Test ####
    $ node index.js
    $ curl localhost:3000
    hola mundo!
