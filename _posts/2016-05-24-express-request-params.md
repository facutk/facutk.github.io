---
layout: page
title: Express request params
tagline: Mean Stack
nav: true
category: mean
tags: mean, express, request, params
comments: false
---

Use the parameters sent to the server in the request.

##### Installation #####

This time we will use [body-parser](https://github.com/expressjs/body-parser) middleware.

    $ npm install --save body-parser

#### server.js ####

We will define a new route: `greet`. We will return the word `hello` + the parameter we receive.

```JavaScript
var express = require('express');
var bodyParser = require('body-parser')

var app = express();

app.use(bodyParser.urlencoded({ extended: false }));

if (app.get('env') === 'development') {
    app.use(require('connect-livereload')());
}

app.use(express.static(__dirname + '/public'));

app.get('/greet/:user?', function(req, res){
    res.send('hello ' + req.params.user);
});

app.listen(3000);
```


##### Test #####

    $ curl localhost:3000/greet/express
    hello express

    $ curl localhost:3000/greet/javascript
    hello javascript

    $curl localhost:3000/greet
    hello undefined
