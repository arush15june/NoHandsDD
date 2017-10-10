

function sendDirection(dir) {
    var xhr = new XMLHttpRequest();
    xhr.open("PUT", "/direction?direction="+dir, true);
    xhr.onload = function (e) {
      if (xhr.readyState === 4) {
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
        document.getElementById("dir").innerHTML = "FORWARD";
        sendDirection("FORWARD");
    }
    else if(e == 115) {
        console.log("STOP");
        document.getElementById("dir").innerHTML = "STOP";
        sendDirection("STOP");
    }
    else if(e == 120) {
        console.log("BACKWARD");
        document.getElementById("dir").innerHTML = "BACKWARD";
        sendDirection("BACKKWARD");
    }
    else if(e == 97) {
        console.log("LEFT");
        document.getElementById("dir").innerHTML = "LEFT";
        sendDirection("LEFT");
    }
    else if(e == 100) {
        console.log("RIGHT");
        document.getElementById("dir").innerHTML = "RIGHT";
        sendDirection("RIGHT");
    }
}, false);

document.addEventListener("gamepadconnected", function(e) {
    console.log("Gamepad connected at index %d: %s. %d buttons, %d axes.",
      e.gamepad.index, e.gamepad.id,
      e.gamepad.buttons.length, e.gamepad.axes.length);
      gamepadHandler(e);
});

document.addEventListener("gamepaddisconnected", function(e) {
    console.log("Gamepad disconnected from index %d: %s",
      e.gamepad.index, e.gamepad.id);
      gamepadHandler(e);
});
var gamepads = {};

function gamepadHandler(event, connecting) {
  var gamepad = event.gamepad;
  // Note:
  // gamepad === navigator.getGamepads()[gamepad.index]

  if (connecting) {
    gamepads[gamepad.index] = gamepad;
  } else {
    delete gamepads[gamepad.index];
  }
}

currentGamepad = gamepads[0];

console.log(gamepads);