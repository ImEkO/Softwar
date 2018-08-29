var zmq       = require('zmq')
  , requester = zmq.socket('req');

const readline = require('readline');
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
      identify(split[0], split[1]);
      break;
    case 'jump':
      console.log('Jump');
      jump(split[0], split[1]);
      break;
    default:
      console.log("No identify");
      break;
  }
  rl.prompt();
}).on('close', () => {
  console.log('Game Over');
  process.exit(0);
});

function identify(cmd,id)
{
  requester.identity = id
  requester.connect('tcp://localhost:3030');
  var replyNbr = 0;
  requester.on('message', function(msg) {
  console.log('got reply', replyNbr, msg.toString());
  replyNbr += 1;
  });

  for (var i = 0; i < 10; ++i) {
    requester.send(cmd);
  }
}

function jump(cmd,id)
{
  requester.identity = id
  requester.connect('tcp://localhost:3030');
  var replyNbr = 0;
  requester.on('message', function(msg) {
  console.log('got reply', replyNbr, msg.toString());
  replyNbr += 1;
  });

  for (var i = 0; i < 2; ++i) {
    requester.send(cmd);
  }
}
