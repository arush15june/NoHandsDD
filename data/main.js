

function sendDirection(dir) {
    var xhr = new XMLHttpRequest();
    xhr.open("POST", "/direction?direction="+dir, true);
    xhr.onload = function (e) {
      if (xhr.readyState === 4) {
        if (xhr.status === 200) {
          console.log(xhr.responseText);
        } else {
          console.error(xhr.statusText);
        }
      }
    };
    xhr.onerror = function (e) {
      console.error(xhr.statusText);
    };
    xhr.send(null);
}

var UP_PRESSED = false;
var DOWN_PRESSED = false;
var LEFT_PRESSED = false;
var RIGHT_PRESSED = false;

document.addEventListener("keypress",function(e) {
    e = e || window.event;
    e = e.keyCode;
    if(e == 119) {
        console.log("FORWARD");
        sendDirection("FORWARD");
        var UP_PRESSED = true;
        var DOWN_PRESSED = false;
        var LEFT_PRESSED = false;
        var RIGHT_PRESSED = false;
    }
    if(e == 115) {
        console.log("DOWN");
        sendDirection("BACKWARD");
        var UP_PRESSED = false;
        var DOWN_PRESSED = true;
        var LEFT_PRESSED = false;
        var RIGHT_PRESSED = false;
    }
    if(e == 95) {
        console.log("LEFT");
        sendDirection("LEFT");
        var UP_PRESSED = false;
        var DOWN_PRESSED = false;
        var LEFT_PRESSED = true;
        var RIGHT_PRESSED = false;
    }
    if(e == 100) {
        console.log("RIGHT");
        sendDirection("RIGHT");
        var UP_PRESSED = false;
        var DOWN_PRESSED = false;
        var LEFT_PRESSED = true;
        var RIGHT_PRESSED = false;
    }
}, false);

// function checkKeyPressAndSend() {
//     if(UP_PRESSED == true) {
//         console.log("FORWARD");
//         sendDirection("FORWARD");
//     }
//     else if(DOWN_PRESSED == true) {
//         console.log("DOWN");
//         sendDirection("BACKWARD");
//     }
//     if(LEFT_PRESSED == true) {
//         console.log("LEFT");
//         sendDirection("LEFT");
//     }
//     if(RIGHT_PRESSED == true) {
//         console.log("RIGHT");
//         sendDirection("RIGHT");
//     }

// }

// setInterval(checkKeyPressAndSend,10);