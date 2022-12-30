require('dotenv').config();
const axios = require('axios');
const FormData = require('form-data');
const { io } = require("socket.io-client");
const fs = require('fs');
// const time = require('time');

async function generateAccessToken(username, password, clientID, grantType) {
  let url = 'https://online-go.com/oauth2/token/';
  let data = new FormData();
  data.append('username', username);
  data.append('password', password);
  data.append('client_id', clientID);
  data.append('grant_type', grantType);

  let res = await axios.post(url, data);
  // console.log(res);
  return res['data']['access_token']
}

async function getUIConfig(accessToken) {
  let url = 'https://online-go.com/api/v1/ui/config';

  let res = await axios.get(url, {
    headers: {
      Authorization: `Bearer ${accessToken}`
    }
  });
  return res['data']
}

async function createDemoBoard(accessToken, boardName, bName, bRank, wName, wRank, width, height, rules, isPrivate) {
  let url = 'https://online-go.com/api/v1/demos';
  let data = new FormData();
  data.append('black_name', bName);
  // data.append('black_pro', 1); // only if ranking is pro
  data.append('black_ranking', bRank);
  data.append('height', height);
  data.append('name', boardName);
  data.append('private', isPrivate);
  data.append('rules', rules);
  data.append('white_name', wName);
  // data.append('white_pro', 1); // only if ranking is pro
  data.append('white_ranking', wRank);
  data.append('width', width);

  let res = await axios.post(url, data, {
    headers: {
      Authorization: `Bearer ${accessToken}`
    }
  });
  console.log('demo board created', res['data']['id']);
  return res['data']['id']
}

function generateOGSSocketHandler() {
  let url = 'https://online-go.com';
  let params = {
    transports: ['websocket']
  };

  let socket = io(url, params);

  socket.on('connect', () => {
    console.log('connected to OGS socket!');
  });
  
  return socket
}

async function downloadSGF(accessToken, reviewID, sgfPath) {
  let url = `https://online-go.com/api/v1/reviews/${reviewID}/sgf/`;

  let res = await axios.get(url, {
    headers: {
      Authorization: `Bearer ${accessToken}`
    }
  });
  let sgf = res['data'];
  fs.writeFile(sgfPath, sgf, (err) => {
    console.log(err);
  });
  return sgf
}

async function getCurrentBoardStates(accessToken, reviewID) {
  let url = `https://online-go.com/termination-api/review/${reviewID}/state`;
  
  let res = await axios.get(url, {
    headers: {
      Authorization: `Bearer ${accessToken}`
    }
  });

  return res['data']['board']

  let currentBoardState = res['data']['board'];
  bState = [];
  wState = [];

  let boardLabels = 'ABCDEFGHJKLMNOPQRST';

  for(let iRow = 0; iRow < 19; iRow++) {
    for(let iCol = 0; iCol < 19; iCol++) {
      if(currentBoardState[iRow][iCol] == 1) {
        let moveString = boardLabels[iRow] + boardLabels[iCol];
        bState.push(moveString);
      } else if(currentBoardState[iRow][iCol] == 2) {
        let moveString = boardLabels[iRow] + boardLabels[iCol];
        wState.push(moveString);
      }
    }
  }

  // console.log('bState: ', bState, '\n');
  // console.log('wState: ', wState, '\n');

  let states = {
    bState,
    wState
  }

  return states
}

module.exports = {
  generateAccessToken,
  getUIConfig,
  generateOGSSocketHandler,
  createDemoBoard,
  downloadSGF,
  getCurrentBoardStates
}