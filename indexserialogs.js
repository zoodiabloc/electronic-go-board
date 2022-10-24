require('dotenv').config();

const { SerialPort } = require('serialport');
const ogsapi = require('./ogsapi.js');
const listener = require('./socket-event-listener.js');
const emitter = require('./socket-event-emitter.js');

const USERNAME = process.env.USERNAME;
const PASSWORD = process.env.PASSWORD;
const CLIENT_ID = process.env.CLIENT_ID;
const GRANT_TYPE = process.env.GRANT_TYPE;
const SERIAL_PORT_PATH = process.env.SERIAL_PORT_PATH;

let boardMoveString = '';

async function main() {
  let accessToken = await ogsapi.generateAccessToken(USERNAME, PASSWORD, CLIENT_ID, GRANT_TYPE);

  let config = await ogsapi.getUIConfig(accessToken);
  let chatAuth = config['chat_auth'];
  let notificationAuth = config['notification_auth'];
  let incidentAuth = config['incident_auth'];
  let userID = config['user']['id'];
  let jwt = config['user_jwt'];

  let reviewID = await ogsapi.createDemoBoard(accessToken, 'test1', 'bplayer', 10, 'wplayer', 10, 19, 19, 'japanese', 'false');

  let socket = await ogsapi.generateOGSSocketHandler();

  listener.listenHostinfo(socket);
  listener.listenAll(socket);
  listener.listenReviewAppendResponse(socket, reviewID);

  await emitter.emitAuthenticate(socket, chatAuth, userID, USERNAME, jwt);  
  await new Promise(resolve => setTimeout(resolve, 1000));
  await emitter.emitConnectReview(socket, chatAuth, reviewID, userID);
  await new Promise(resolve => setTimeout(resolve, 1000));

  const port = new SerialPort({
    path: SERIAL_PORT_PATH,
    baudRate: 9600,
    autoOpen: true
  });

  port.on('error', (err) => {
    console.log('Error: ', err.message);
  });

  port.on('readable', async function () {
    let newMove = port.read().toString().replace('\n', '');
    console.log('new move:', newMove);
    boardMoveString += newMove;
    console.log('new board move string:', boardMoveString);

    await emitter.emitReviewAppendMove(socket, boardMoveString, reviewID, userID);
  });
}

main();