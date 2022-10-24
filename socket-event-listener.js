function listenReviewFullState(socket, reviewID) {
  let eventName = `review/${reviewID}/full_state`;
  socket.on(eventName, (msg) => {
    console.log(msg);
  });
  console.log('listening to listenReviewFullState');
}

function listenReviewMoveResponse(socket, reviewID) {
  let eventName = `review/${reviewID}/r`;
  socket.on(eventName, (msg) => {
    console.log(msg);
  });
  console.log('listening to listenReviewMoveResponse');
}

function listenHostinfo(socket) {
  let eventName = 'hostinfo';
  socket.on(eventName, (msg) => {
    console.log(msg);
  });
  console.log('listening to listenHostinfo');
}

function listenAll(socket) {
  socket.onAny((eventName, msg) => {
    console.log(eventName);
  });
  console.log('listening to listenAll');
}

// rename to listenReviewAppendResult later
function listenReviewAppendResponse(socket, reviewID) {
  let eventName = `review/${reviewID}/r`;
  socket.on(eventName, (msg) => {
    console.log(msg);
  });
  console.log('listening to listenReviewAppendResponse');
}

module.exports = {
  listenReviewFullState,
  listenReviewMoveResponse,
  listenHostinfo,
  listenAll,
  listenReviewAppendResponse
}