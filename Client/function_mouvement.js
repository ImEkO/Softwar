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

function forward(cmd, id, line)
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

function backward(cmd, id, line)
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
