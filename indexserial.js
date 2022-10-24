

const { SerialPort } = require('serialport')
const { ReadlineParser } = require('@serialport/parser-readline');

const port = new SerialPort({ path: '/dev/pts/4', baudRate: 9600, autoOpen: true })

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
  console.log('Data:', str)
})
