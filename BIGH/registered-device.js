
/*
org=sg7mmg
type=nodejsexample
id=AABBCCDDEEFF
auth-method=token
auth-token=h4ZHSAxP1Nzl3W_@X6
*/

var clientid = 'd:jz5ix3:arduino:123';   
/*
org = "jz5ix3";
deviceType = "arduino";
deviceId = "123";
authToken = "OocewT@k5@8BG8WFHY";
clientId = "d:" + org + ":" + deviceType + ":" + deviceId;
dataSet = "test";
*/


var mqtt     = require('mqtt');

var username = 'use-token-auth';
var password = 'OocewT@k5@8BG8WFHY';
var topic    = 'iot-2/evt/status/fmt/json';
var server   = 'mqtt://jz5ix3.messaging.internetofthings.ibmcloud.com';
var client   = mqtt.connect(server, { clientId: clientid, username: username, password: password});
  
function start() {
  setTimeout(start, 1000);
  var temperature = Math.random() * 2 + 20;
  var jsonData    = {'d':{'myName': 'NodeJS Client', 'temperature': temperature}};
  var payload     = JSON.stringify(jsonData);
  console.log(payload);
  client.publish(topic, payload); 
}

start();
