---
layout: page
title: Gulp Nodemon Livereload
tagline: Mean Stack
nav: true
category: mean
tags: mean, express, gulp, nodemon, livereload
comments: false
---

Add gulp tasks to restart the server and reload the browser on changes.

##### Dependencies #####

We are gonna be using the following gulp plugins:

- [gulp-nodemon](https://www.npmjs.com/package/gulp-nodemon)
: Restart our express server on changes on the server.

- [tiny-lr](https://www.npmjs.com/package/tiny-lr)
: Notify the browser on changes in the files.


In addition, we will use this express middleware to inject code in the pages we serve.

- [connect-livereload](https://www.npmjs.com/package/connect-livereload)
: Adds dinamically the livereload script, which then polls information from our servers and reloads the page when notified.

##### Installation #####

    $ npm install --savedev gulp path gulp-nodemon tiny-lr connect-livereload

#### package.json ####

Our `package.json` should look like this now.

```JavaScript
{
  "name": "backend",
  "version": "1.0.0",
  "description": "",
  "main": "server.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "author": "",
  "license": "ISC",
  "devDependencies": {
      "gulp-nodemon": "2.0.7",
      "path": "^0.12.7",
      "tiny-lr": "^0.2.1",
      "connect-livereload": "^0.5.4"
  },
  "dependencies": {
    "express": "^4.13.4",
    "gulp": "^3.9.1"
  }
}
```

##### Files #####

This should be the contents of our directory.

    backend/
        public/
            index.html
        node_modules
        package.json
        server.js
        gulpfile.js

#### server.js ####

If we are running in a dev environment, include `connect-livereload` middleware.

```JavaScript
var express = require('express');

var app = express();

if (app.get('env') === 'development') {
    app.use(require('connect-livereload')());
}

app.use(express.static(__dirname + '/public'));

app.listen(3000);
```

##### Why connect-livereload? #####

We see that we are serving the static files located in `public/`.

For the moment, the only file we have is `index.html`.

If we check the contents of our file.

    $ cat public/index.html
    <!DOCTYPE html>
    <html>
        <head>
            <meta charset="utf-8">
        </head>
        <body>
            <h1>Hello World!</h1>
        </body>
    </html>

However, if check the source in the browser, we can see a piece of script was added.
![connect-livereload source]({{ site.url }}/assets/2016-05-23-gulp-nodemon-livereload-01.png)

This script is listening for changes on the port `35729`.
![connect-livereload listening]({{ site.url }}/assets/2016-05-23-gulp-nodemon-livereload-02.png)


#### gulpfile.js ####

Our new `gulpfile` does the following:

- `tiny-lr` watches for changes on our `html` files
    - Notifies browsers via port `35729`.
- `gulp-nodemon` watches for changes on the `server.js`.
    - Restarts the `server.js`

The script is the following.

```JavaScript
var gulp = require('gulp');
var nodemon = require('gulp-nodemon');
var path = require('path');
var tinylr = require('tiny-lr');

/* Create livereload server */
gulp.task('livereload', function() {
    tinylrNotifier = tinylr();
    tinylrNotifier.listen(35729);  
});

/* Notify browser on static file changes */
gulp.watch('public/*.*', function (event) {
    var fileName = path.relative(__dirname, event.path);
    tinylrNotifier.changed({
        body: {
            files: [fileName]
        }
    });
});

/* Restart server on server changes */
gulp.task('nodemon', function () {
    nodemon({
        script: 'server.js',
        ext: 'html js'
    })
    .on('restart', function () {
        console.log('server restarted!')
    })
});

/* Define default task */
gulp.task('default', ['nodemon', 'livereload'], function() {

});
```

#### Test ####

Now we start our project by running.

    $ gulp

We can live edit the files and view the result in the browser as soon as we save.

![connect-livereload listening]({{ site.url }}/assets/2016-05-23-gulp-nodemon-livereload-03.gif)
