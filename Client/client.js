var zmq       = require('zmq')
  , requester = zmq.socket('req');

var randString = function() {
  var len = 10
    , charSet = '0123456789abcdef'
    , result = [];

  for (var i = 0; i < len; ++i) {
    result.push(charSet[Math.floor(Math.random() * charSet.length)]);
  }
  result.splice(len / 2, 0, ['-']);
  return result.join('');
};

requester.identity = randString();
requester.connect('tcp://localhost:3030');
var replyNbr = 0;
requester.on('message', function(msg) {
  console.log('got reply', replyNbr, msg.toString());
  replyNbr += 1;
});

for (var i = 0; i < 10; ++i) {
  requester.send("Hello");
}
