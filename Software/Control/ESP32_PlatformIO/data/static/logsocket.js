document.addEventListener('DOMContentLoaded', function() {
    console.log("Trying to connect to log websocket");
    
    var logSocket = new WebSocket("ws://" + location.hostname + ":81/log");
    logSocket.onopen = function(event) {
        console.log("logSocket: onOpen: " + event);
    };

    logSocket.onmessage = function(event) {
        console.log("logSocket: Got: " + event.data);
        document.getElementById('debugLog').value += event.data;
    };

}, false);

