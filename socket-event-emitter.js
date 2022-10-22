// const time = require('time');

async function emitAuthenticate(socket, chatAuth, playerID, username, jwt) {
  let eventName = 'authenticate';
  let data = {
    auth: chatAuth,
    player_id: playerID,
    jwt: jwt,
    username: username

    // username: username,
    // jwt
  };
  socket.emit(eventName, data);
  console.log('emitting emitAuthenticate');
  // await time.sleep(1000);
}

async function emitConnectReview(socket, chatAuth, reviewID, playerID) {
  let eventName = 'review/connect';
  let data = {
    auth: chatAuth,
    review_id: reviewID,
    player_id: playerID
  };
  socket.emit(eventName, data);
  console.log('emitting emitConnectReview');
}

async function emitHostinfo(socket) {
  let eventName = 'hostinfo';
  socket.emit(eventName);
  console.log('emitting emitHostinfo');
}

async function emitConnectChat() {

}

async function emitConnectNotification(socket, notificationAuth, playerID) {
  let eventName = 'notification/connect';
  let data = {
    auth: notificationAuth,
    // review_id: reviewID,
    player_id: playerID
  };
  socket.emit(eventName, data);
  console.log('emitting emitConnectNotification');
}

async function emitConnectIncident() {

}

async function emitReviewAppendMove(socket, updatedMoveString, reviewID, playerID) {
  let eventName = 'review/append';
  let data = {
    f: 0,
    t: '',
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
  emitHostinfo,
  emitConnectNotification
}