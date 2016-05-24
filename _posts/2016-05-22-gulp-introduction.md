---
layout: page
title: Gulp Introduction
tagline: Mean Stack
nav: true
category: mean
tags: mean, gulp, introduction
comments: false
---

Minimal intro to gulp API.

We are gonna be running basic examples for:

- tasks
- task dependencies
- watch
- src / pipe / dest
- plugins

For a more rich guide, you can refer to the official [Gulp docs](https://github.com/gulpjs/gulp/blob/master/docs/API.md).

#### Installation ####

To start with, we need to install gulp globally. We run the following command.

    $ npm install --global gulp-cli

After this, we'll create a mini test project just to play with gulp.

    $ mkdir gulptest && cd gulptest
    $ npm init
    $ npm install --save gulp
    $ touch gulpfile.js

File structure will be the following.

    gulptest/
        node_modules/
        index.js
        package.json
        gulpfile.js


#### Hello World ####

Now, let's start with the most basic gulp file. We'll just show a 'Hello world!' on the console.

##### gulpfile.js #####

```JavaScript
var gulp = require('gulp');

/* Define default task */
gulp.task('default', function() {
    console.log("hello world!");
});
```

We test it by simple running `gulp` in the same folder as our `gulpfile.js`.

    $ gulp
    [12:02:05] Using gulpfile ~\gulptest\gulpfile.js
    [12:02:05] Starting 'default'...
    hello world!
    [12:02:05] Finished 'default' after 224 μs



#### Task Dependencies ####

This time, a dependency for the `default` task is going to be the `hello` task.

##### gulpfile.js #####

```JavaScript
var gulp = require('gulp');

gulp.task('hello', function(){
    console.log("hello dependency!");
});

/* Define default task with hello dependency */
gulp.task('default', ['hello'], function() {

});
```

We run it again.

    $ gulp
    [13:34:34] Using gulpfile ~\gulptest\gulpfile.js
    [13:34:34] Starting 'hello'...
    hello dependency!
    [13:34:34] Finished 'hello' after 107 μs
    [13:34:34] Starting 'default'...
    [13:34:34] Finished 'default' after 6.64 μs


#### Watch ####

We are going to add a `source` folder with a file named `words.txt`.

    gulptest/
        node_modules/
        source/          <!-- new folder -->
            words.txt    <!-- new file -->
        index.js
        package.json
        gulpfile.js

Our `gulpfile` this time will check on changes on the files in this folder.
In case on any change, will report it in the console.

##### gulpfile.js #####

```JavaScript
var gulp = require('gulp');

/* log changes in the files of our /source folder */
gulp.watch('source/*.*', function(event) {
  console.log('File ' + event.path + ' was ' + event.type);
});

gulp.task('default', function() {

});
```

We run our `gulpfile`.

    $ gulp
    [15:39:28] Using gulpfile ~\gulptest\gulpfile.js
    [15:39:28] Starting 'default'...
    [15:39:28] Finished 'default' after 61 μs

This time instead of starting and stopping, it stays waiting.

When we touch the file `source/words.txt`, we see the following in our terminal:

    File ~\gulptest\source\words.txt was changed



#### Src / Dest ####

Using the same file structure as before.

    gulptest/
        node_modules/
        source/
            words.txt
        index.js
        package.json
        gulpfile.js

This time we create a gulp task to copy all the files from `source` into `build`.

##### gulpfile.js #####

```JavaScript
var gulp = require('gulp');

/* copy files from /source to /build */
gulp.src('source/*.*')
.pipe(gulp.dest('build'));

gulp.task('default', function() {

});
```

We run our script.

    $ gulp

And we will find a new folder `build` with all the contents from `source`.

    gulptest/
        node_modules/
        source/
            words.txt
        build/
            words.txt    <!-- copied by our task -->
        index.js
        package.json
        gulpfile.js

#### Plugins ####

There are several [Plugins](http://gulpjs.com/plugins/) we can use to help us in our development.

Some of the most used ones are the following:

- [gulp-jslint](https://www.npmjs.com/package/gulp-jslint)
: Check for javascript syntax errors.

- [gulp-minify](https://www.npmjs.com/package/gulp-minify)
: Minify files.

- [gulp-concat](https://github.com/contra/gulp-concat)
: Concatenate files.
