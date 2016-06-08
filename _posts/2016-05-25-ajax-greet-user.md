---
layout: page
title: AJAX greet user
tagline: Mean Stack
nav: true
category: mean
tags: mean, AJAX, http, get, html, javascript
comments: false
---

Use plain old javascript [AJAX](https://developer.mozilla.org/en-US/docs/AJAX/Getting_Started) to interact with the backend.

We are moving towards a single page application.
This means, we don't want to reload the page on every interaction with the server.
We want our contents to change dinamically.

We will start this path by using the native method in javascript, no libraries or frameworks in this chapter.

#### Boilerplate code ####

In order to try AJAX, we will first change a bit our files, add some fields and test the interaction.

##### Files #####

Inside the `/public` folder, we create a new file called `app.js`.

    backend/
        public/
            index.html
            app.js        <!-- new file: app.js -->
        node_modules
        package.json
        index.js

#### index.html ####

For this test we'll change the layout a bit.

We add following elements:

- An `input` of `type`:text with `id` name.
- A `button` with `id` send.
- A `script` tag pointing to `app.js`

```html
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
    </head>
    <body>
        <h1 id="greeting">AJAX demo</h1>

        <p>
            Name: <input id="name" type="text" name="name" value="" />
            <input type="button" id="send" value="send" />
        </p>

        <script src="app.js" charset="utf-8"></script>
    </body>
</html>
```

#### app.js ####

For this first part, we won't communicate with the server yet.

Every time we click on the `send` button, the contents of the `name` box are printed on the console.

```JavaScript
document.getElementById("send").onclick = function() {
    console.log( document.getElementById("name").value );
};
```

##### Test #####

To try this:

- we will go to [localhost:3000](localhost:3000).
- Open the console (F12 on Chrome).
- Enter a name and click `send`.

![send-click-console-log]({{ site.url }}/assets/2016-05-25-ajax-greet-user-01.gif)

You should see your names being printed in the console.

As you can check in the `Network` tab of the Console, no information is traveling back and forth from the server.

Next up, we will change this.


#### AJAX ####

Now that we have all in place, we want to interact with our server.

In our last chapter we created an endpoint in our server `greet`.

It takes a `parameter` and returns: `hello` + `parameter`

    $ curl localhost:3000/greet/express
    hello express

This time, when we click on the `send` button, a couple of interesting things will happen.

- We will store the `name` in a variable.
- We will call our server into `/greet` + `name`.
- Server will answer.
- We will display it's answer.

#### app.js ####

We need to edit `app.js` with the following code to achieve this functionality.

```JavaScript
/* when we click send */
document.getElementById("send").onclick = function() {

    /* store the contents of the box into a variable */
    var name = document.getElementById("name").value;

    /* create a new request */
    httpRequest = new XMLHttpRequest();

    /* call our server on localhost:3000/greet/name */
    httpRequest.open('GET', 'greet/' + name );
    httpRequest.send();

    /* when the request is answered*/
    httpRequest.onreadystatechange = function(){

        /* if it's done */
        if (httpRequest.readyState === XMLHttpRequest.DONE) {

            /* and the status is 200 */
            if (httpRequest.status === 200) {

                /* replace the contents of our greeting with the answer */
                document.getElementById("greeting").innerHTML = httpRequest.responseText;
            }
        }
    };

};
```

#### Test ####

Go ahead and open your browser on [localhost:3000](localhost:3000).

Try as before, entering a name and clicking on send.

This time, pay attention to the `Network` tab in the Console.

![send-click-server-response]({{ site.url }}/assets/2016-05-25-ajax-greet-user-02.gif)

As you can see:

- Our page is calling our server.
- The server is answering.
- The answer has status 200.
- The response has text: `hello` + the `name`
- We place that response as our greeting.

#### Conclusion ####

We've covered a lot of ground in this lesson.

- Javascript
- AJAX
    - request
    - response
- HTTP Status Codes

As you've seen, using plain old javascript is quite verbose.

In following chapters we will migrate into a library to achieve this same functionality using a lot less code.
