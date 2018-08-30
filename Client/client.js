var zmq       = require('zmq')
  , requester = zmq.socket('req');

/*const readline = require('readline');
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  prompt: 'Command > '
});

rl.prompt();

rl.on('line', (line) => {
  var split = line.split("|");
  console.log(split);
  switch (split[0]) {
    case 'identify':
      console.log('Identify');
      identify(split[0], split[1], line);
      break;
    case 'jump':
      console.log('Jump');
      jump(split[0], split[1], line);
      break;
    default:
      console.log("No identify");
      break;
  }
  rl.prompt();
}).on('close', () => {
  console.log('Game Over');
  process.exit(0);
});*/

var identifier = "OxO"+randomIntInc(1, 10)
identify("identify", identifier, "identify|"+identifier);
switch (randomIntInc(1, 13)) {
  case 1:
    console.log('Jump');
    jump("jump", "null", "jump|null");
    break;
  case 2:
    console.log('Forward');
    jump("forward", "null", "forward|null");
    break;
  case 3:
    console.log('Backward');
    jump("backward", "null", "backward|null");
    break;
  case 4:
    console.log('leftfwd');
    jump("leftfwd", "null", "leftfwd|null");
    break;
  case 5:
    console.log('rightfwd');
    jump("rightfwd", "null", "rightfwd|null");
    break;
  case 6:
    console.log('right');
    jump("right", "null", "right|null");
    break;
  case 7:
    console.log('left');
    jump("left", "null", "left|null");
    break;
  case 8:
    console.log('looking');
    jump("looking", "null", "looking|null");
    break;
  case 9:
    console.log('gather');
    jump("gather", "null", "gather|null");
    break;
  case 10:
    console.log('watch');
    jump("watch", "null", "watch|null");
    break;
  case 11:
    console.log('attack');
    jump("attack", "null", "attack|null");
    break;
  case 12:
    console.log('selfid');
    jump("selfid", "null", "selfid|null");
    break;
  case 13:
    console.log('selfstats');
    jump("selfstats", "null", "selfstats|null");
    break;
  default:
    console.log("No identify");
    break;
}

function randomIntInc(low, high) {
  return Math.floor(Math.random() * (high - low + 1) + low)
}

function identify(cmd, id, line)
{
  requester.identity = id
  requester.connect('tcp://localhost:4242');
  var replyNbr = 0;
  requester.on('message', function(msg) {
  console.log('got reply', replyNbr, msg.toString());
  replyNbr += 1;
  });

  for (var i = 0; i < 10; ++i) {
    requester.send(line);
  }
}

function jump(cmd, id, line)
{
  requester.identity = id
  requester.connect('tcp://localhost:4242');
  var replyNbr = 0;
  requester.on('message', function(msg) {
  console.log('got reply', replyNbr, msg.toString());
  replyNbr += 1;
  });

  for (var i = 0; i < 2; ++i) {
    requester.send(line);
  }
}

function forward(cmd, id, line)
{
  requester.identity = id
  requester.connect('tcp://localhost:4242');
  var replyNbr = 0;
  requester.on('message', function(msg) {
  console.log('got reply', replyNbr, msg.toString());
  replyNbr += 1;
  });

  for (var i = 0; i < 2; ++i) {
    requester.send(line);
  }
}

function backward(cmd, id, line)
{
  requester.identity = id
  requester.connect('tcp://localhost:4242');
  var replyNbr = 0;
  requester.on('message', function(msg) {
  console.log('got reply', replyNbr, msg.toString());
  replyNbr += 1;
  });

  for (var i = 0; i < 2; ++i) {
    requester.send(line);
  }
}
