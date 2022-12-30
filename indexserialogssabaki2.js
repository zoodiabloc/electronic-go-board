require('dotenv').config();
const Board = require('@sabaki/go-board');

const { SerialPort } = require('serialport');
const ogsapi = require('./ogsapi.js');
const listener = require('./socket-event-listener.js');
const emitter = require('./socket-event-emitter.js');

const USERNAME = process.env.USERNAME;
const PASSWORD = process.env.PASSWORD;
const CLIENT_ID = process.env.CLIENT_ID;
const GRANT_TYPE = process.env.GRANT_TYPE;
const SERIAL_PORT_PATH = process.env.SERIAL_PORT_PATH;

const ARDUINO_LABELS = 'ABCDEFGHIJKLMNOPQRS';
const OGS_LABELS = 'ABCDEFGHIJKLMNOPQRS';

const boardLabels = 'ABCDEFGHIJKLMNOPQRS';

let boardMoveString = '';
let serialBuffer = '';
let moveCount = 0;
let board = new Board([
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
])

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
  	let str = port.read().toString();
		console.log('str is ', str)
    serialBuffer += str;

    if(serialBuffer.length < 2) {
      console.log('serialBuffer isn\'t full yet');
		} else if(serialBuffer.length == 2) {

			console.log('serialBuffer is full: ', serialBuffer);

			let isValid = validateNewMove(board, serialBuffer, moveCount++, ARDUINO_LABELS);
			console.log('isValid: ', isValid);

			if(isValid){
				moveCount++;
				// boardMoveString += serialBuffer;
				board = updateBoard(board, moveCount, serialBuffer, boardLabels);
				console.log('ARDUINO_LABELS.indexOf(serialBuffer[0]): ', ARDUINO_LABELS.indexOf(serialBuffer[0]))
				console.log('ARDUINO_LABELS.indexOf(serialBuffer[1]): ', ARDUINO_LABELS.indexOf(serialBuffer[1]))
				console.log("'abc'.indexOf('c'): ", 'abc'.indexOf('c'))

				ogsLabelR = OGS_LABELS[ARDUINO_LABELS.indexOf(serialBuffer[0])]
				ogsLabelC = OGS_LABELS[ARDUINO_LABELS.indexOf(serialBuffer[1])]
				console.log('ogsLabelR: ', ogsLabelR)
				console.log('ogsLabelC: ', ogsLabelC)
				newOGSMove = ogsLabelR+ogsLabelC
				console.log('new move: ', ogsLabelR+ogsLabelC)
				boardMoveString += newOGSMove;

				await emitter.emitReviewAppendMove(socket, '' + boardMoveString, reviewID, userID)
			}

			serialBuffer = '';
		} else {
			serialBuffer = '';
		}

		
	});
}

function validateNewMove(board, newMoveString, newMoveCount, boardLabels) {
	let iRow = boardLabels.indexOf(newMoveString[0])
	let iColumn = boardLabels.indexOf(newMoveString[1])

	let result = board.analyzeMove(newMoveCount%2==0?-1:1, [iRow, iColumn]);
	return !result.overwrite
}

function updateBoard(board, moveCount, newMove, boardLabels) {
	let moveColour = moveCount%2==0?-1:1;
	console.log('moveColour: ', moveColour);
	let moveRow = boardLabels.indexOf(newMove[0]);
	console.log('moveRow: ', moveRow);
	let moveColumn = boardLabels.indexOf(newMove[1]);
	console.log('moveColumn: ', moveColumn);
	let updatedBoard = board.makeMove(moveColour, [moveRow, moveColumn]);
	return updatedBoard
}

main();