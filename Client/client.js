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

var identifier = "OXO"+random()
identify("identify", identifier, "identify|"+identifier);
switch (urand()) {
  case 1:
    console.log('Jump');
    jump("jump", "null", "jump|null");
    break;
  default:
    console.log("No identify");
    break;
}

function identify(cmd, id, line)
{
  requester.identity = id
  requester.connect('tcp://localhost:3030');
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
  requester.connect('tcp://localhost:3030');
  var replyNbr = 0;
  requester.on('message', function(msg) {
  console.log('got reply', replyNbr, msg.toString());
  replyNbr += 1;
  });

  for (var i = 0; i < 2; ++i) {
    requester.send(line);
  }
}
