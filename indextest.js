require('dotenv').config();

const ogsapi = require('./ogsapi.js');
const listener = require('./socket-event-listener.js');
const emitter = require('./socket-event-emitter.js');

const USERNAME = process.env.USERNAME;
const PASSWORD = process.env.PASSWORD;
const CLIENT_ID = process.env.CLIENT_ID;
const GRANT_TYPE = process.env.GRANT_TYPE;

async function main() {
  let accessToken = await ogsapi.generateAccessToken(USERNAME, PASSWORD, CLIENT_ID, GRANT_TYPE);
  
  let config = await ogsapi.getUIConfig(accessToken);
  let chatAuth = config['chat_auth'];
  let notificationAuth = config['notification_auth'];
  let incidentAuth = config['incident_auth'];
  let userID = config['user']['id'];
  let jwt = config['user_jwt'];

  // let reviewID = await ogsapi.createDemoBoard(accessToken, 'test1', 'bplayer', 10, 'wplayer', 10, 19, 19, 'japanese', 'false');
  let reviewID = 959865;

  let socket = await ogsapi.generateOGSSocketHandler();

  listener.listenHostinfo(socket);

  listener.listenAll(socket);

  listener.listenReviewAppendResponse(socket, reviewID);
  
  emitter.emitAuthenticate(socket, chatAuth, userID, USERNAME, jwt);

  emitter.emitConnectReview(socket, chatAuth, reviewID, userID);

  emitter.emitReviewAppendMove(socket, 'ddeeffgg', reviewID, userID);

  emitter.emitHostinfo(socket);

  let sgf = await ogsapi.downloadSGF(accessToken, reviewID, './sgf/test.sgf');
  console.log(sgf);
}

main();