

const { SerialPort } = require('serialport')
const { ReadlineParser } = require('@serialport/parser-readline');

const port = new SerialPort({ path: '/dev/ttyACM0', baudRate: 9600, autoOpen: true })

let buffer = '';

port.write('main screen turn on', function(err) {
  if (err) {
    return console.log('Error on write: ', err.message)
  }
  console.log('message written')
})

// Open errors will be emitted as an error event
port.on('error', function(err) {
  console.log('Error: ', err.message)
})

// Read data that is available but keep the stream in "paused mode"
port.on('readable', function () {
	let str = port.read().toString();
  // console.log('Data tostring:', str)
  // console.log('Data:', port.read());
  buffer += str;
  if(buffer.length < 2) {
    console.log('buffer isn\'t full yet');
  } else {
    console.log('buffer is full: ', buffer);
    buffer = '';
  }
  // console.log('buffer: ', buffer)
})
