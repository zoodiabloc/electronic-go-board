function emitAuthenticate(socket, chatAuth, playerID, username, jwt) {
  let eventName = 'authenticate';
  let data = {
    auth: chatAuth,
    player_id: playerID,
    username: username,
    jwt
  };
  socket.emit(eventName, data);
  console.log('emitting emitAuthenticate');
}

function emitConnectReview(socket, chatAuth, reviewID, playerID) {
  let eventName = 'review/connect';
  let data = {
    auth: chatAuth,
    review_id: reviewID,
    player_id: playerID
  };
  socket.emit(eventName, data);
  console.log('emitting emitConnectReview');
}

function emitHostinfo(socket) {
  let eventName = 'hostinfo';
  socket.emit(eventName);
  console.log('emitting emitHostinfo');
}

function emitConnectChat() {

}

function emitConnectNotification() {

}

function emitConnectIncident() {

}

function emitReviewAppendMove(socket, updatedMoveString, reviewID, playerID) {
  let eventName = 'review/append';
  let data = {
    f: 0,
    t: ' ',
    m: updatedMoveString,
    k: {},
    review_id: reviewID,
    player_id: playerID
  };
  socket.emit(eventName, data);
  console.log('emitting emitReviewAppendMove');
}

module.exports = {
  emitAuthenticate,
  emitConnectReview,
  emitReviewAppendMove,
  emitHostinfo
}