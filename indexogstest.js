require('dotenv').config();

const ogsapi = require('./ogsapi.js');
const listener = require('./socket-event-listener.js');
const emitter = require('./socket-event-emitter.js');
// const ogsapi2 = require('./ogsapi2.js');

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

  let reviewID = await ogsapi.createDemoBoard(accessToken, 'test1', 'bplayer', 10, 'wplayer', 10, 19, 19, 'japanese', 'false');
  console.log('reviewID: ', reviewID)
  // let reviewID = 967620;

  let socket = await ogsapi.generateOGSSocketHandler();

  // listener.listenHostinfo(socket);

  // listener.listenAll(socket);

  // listener.listenReviewAppendResponse(socket, reviewID);

  await new Promise(resolve => setTimeout(resolve, 1000));
  
  await emitter.emitAuthenticate(socket, chatAuth, userID, USERNAME, jwt);  

  await new Promise(resolve => setTimeout(resolve, 1000));

  await emitter.emitConnectReview(socket, chatAuth, reviewID, userID);

  await new Promise(resolve => setTimeout(resolve, 1000));

  await emitter.emitReviewAppendMove(socket, 'AABB', reviewID, userID);

  await new Promise(resolve => setTimeout(resolve, 1000));

  // await emitter.emitHostinfo(socket);

  // let sgf = await ogsapi.downloadSGF(accessToken, reviewID, './sgf/test.sgf');
  // console.log(sgf);

  // let states = await ogsapi.getCurrentBoardStates(accessToken, reviewID)
  // console.log(states);

  let states = await ogsapi.getCurrentBoardStates(accessToken, reviewID);
  console.log(states);

}

main();