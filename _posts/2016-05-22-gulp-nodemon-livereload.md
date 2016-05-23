---
layout: page
title: Gulp Nodemon Livereload
tagline: Mean Stack
nav: true
category: mean
tags: mean, express, gulo, nodemon, livereload
---

Add gulp with tasks to restart the server when is changed and reload the browser page on changes.

    $ npm install gulp -g
    $ npm install --savedev gulp path gulp-nodemon tiny-lr connect-livereload

- [gulp-nodemon](https://www.npmjs.com/package/gulp-nodemon)
- [tiny-lr](https://www.npmjs.com/package/tiny-lr)
- [connect-livereload](https://www.npmjs.com/package/connect-livereload)
- [gulp with live reload tutorial](https://community.nitrous.io/tutorials/setting-up-gulp-with-livereload-sass-and-other-tasks)


##### Ls #####
    backend/
        public/
            index.html     <!-- new file: /public/index.html -->
        node_modules
        package.json       <!-- edited -->
        server.js          <!-- renamed from index.js and edited -->
        gulpfile.js        <!-- new file -->


#### package.json ####
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

#### server.js ####

If we are running in a dev environment, include 'connect-livereload' middleware.

```JavaScript
var express = require('express');

var app = express();

if (app.get('env') === 'development') {
    app.use(require('connect-livereload')());
}

app.use(express.static(__dirname + '/public'));

app.listen(3000);
```

#### gulpfile.js ####

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
    $ gulp

#### Browser test ####
TODO
