# electronic-go-board

## Prerequisite

Create a new application from https://online-go.com/oauth2/applications/ and set the grant type to **password**

Create a .env file in the root directory containing the following variables:
- USERNAME: ogs username
- PASSWORD: ogs password
- CLIENT_ID: client ID from the new application
- GRANT_TYPE: 'password'

## How to initialize the application

`npm install`

## How to combine the Arduino and the JavaScript codes

Connect the 4 by 4 keypad pins to the Arduino I/O pins. Relocate the Arduino library files to the directory your Arduino installation uses to store the library files. In my case it's Linux Mint and it's under /home/username/Arduino/libraries/. You create a new folder under this directory and place all the files inside that folder. Consult the Arduino documentation to see how things work. I don't know it that well XD

Load the go-board.ino sketch .ino file into the Arduino chip and start the Arduino. Start the JavaScript code using `node indexserialogs.js`. Open the new demo board in a web browser and press on the keys to see the moves being appended to the new demo board.

If the keys you press and the actual moves on OGS do not align, adjust line 24 and 25 of the go-board.ino sketch under they match.

## How to create virtual serial port pair and register them in the program ... in Linux

I am not sure how to work with Windows, so this is only for Linux. You can create a virtual serial port pair using the command `socat -d -d pty,raw,echo=0 pty,raw,echo=0`. This returns something like this

> 2022/10/22 13:00:52 socat[3281] N PTY is /dev/pts/1
>
> 2022/10/22 13:00:52 socat[3281] N PTY is /dev/pts/2
>
> 2022/10/22 13:00:52 socat[3281] N starting data transfer loop with FDs [5,5] and [7,7]

This pair of virtual serial port allow you to test the sending and receiving in your application. If you send one, the other one will receive something and vice versa.

The numbers might be different. In this case the first virtual serial port is **/dev/pts/1** and the second virtual serial port is **/dev/pts/2**. Copy the path of the second virtual serial port, ie in this case `dev/pts/2` to .env as a new variable called `SERIAL_PORT_PATH`.

After starting the application with the command in the next section in one terminal, use the path of the first virtual serial port in this command to issue a new move to the new demo board: `echo "test" > /dev/pts/1` in a different terminal.

After submitting you should see a new `review/<reviewID>/r` event being captured from the first terminal. Its **m** field should contain the current board's move string. If you see this, the program is working.

## How to run the application

`node indexserialogs.js`

## Project updates

### Succeeded with 9 by 9 matrix (2022.12.30)

Use indexserialogssabaki2.js to communicate with the Arduino board and OGS.

### Support playing on OGS with a 4 by 4 keypad (2022.10.27)

I add the Arduino sketch and library codes as well as modify the main file to support playing on OGS with a 4 by 4 keypad. Modify the pin number if you decide to try it on your own Arduino board. The four library files need to be added to the library directory of your Arduino installation. When everything is ready, run `node indexserialogs.js` and start the Arduino. You can view your game if you go to your demo board on OGS. You need to refresh the web page if you want to see updated board states.

### Sending move strings through virtual serial port is working -ish (2022.10.23)

I can use virtual serial port to send over move strings one a time, simulating a game played between two players. You need to create a pair of virtual serial ports first before running the main program.

### Append new moves is now working (2022.10.22)

The appending moves to a demo board has been tested and it works. Some sleep functions has been implemented to leave enough time for the server to properly authenticating users. 

To use and test the library's ability to append moves, run `npm start` to create a new demo board in a terminal (terminal 1) and to listen for responses from the socket connection.

Go to `indextest.js`. On line 24, modify the value of the reviewID variable to match the demo board ID shown in terminal 1. Also, on line 44, modify the second argument of the `await emitter.emitReviewAppendMove` function call. This argument is the string representation of the updated board state.

In a different termal (terminal 2), run `node indextest.js` to append the new move you define. Well it's more like setting the board to your defined state.

You should see that in both terminal 1 and terminal 2 there is a new event received from the server in our socket connection. The message should be `review/<reviewID>/r` and it should contain the new board state in the m field.

If you go to OGS to view the new demo board **https://online-go.com/demo/view/<reviewID>** or refresh the page if you're already there, you should see the board with the new state!

### Current steps to make appending moves works (2022.10.17)

1. Run `npm start` and copy the new demo board ID from the terminal.
2. On line 23 of indextest.js, modify the value of `reviewID` to match the new demo board ID from step 1.
3. Run `node indextest.js` in another terminal.
4. Both index.js and indextest.js listen to all incoming messages and output the event name. If appending moves is successful, you should see a new entry of `review/<reviewID>/r` which is normally sent back from the socket once appending move to a review is successful. However, running step 1 through 3 won't see this behaviour, meaning the appending moves did not work yet.
5. Open ogs and log in with your username and password.
6. Open a new demo board and name it anything.
7. Once a new board is created, go to the url bar and change the demo board ID to the board ID you received from step 1.
8. Make a few moves. You should see new entries in both terminal because the website successfully append moves to the demo board.
9. Now stop the terminal used to run `node indextest.js` in step 3 and rerun it again.
10. You should see now it IS properly appending moves to the board we created from step 1.
11. If you stop the `node indextest.js` terminal now and add more lines of `emitter.emitReviewAppendMove(socket, 'abcdefgheeijjiddii', reviewID, userID);` with different move strings, ie modify `abcdefgheeijjiddii` to something else, you should see that appending these moves to the board is successful.
12. But if you wait for too long without doing anything, you'll have to re-log in your account to get the same effect.
13. If that still doesn't work, sometimes go to the web browser and move the game backwards until there is no stone will do the trick.
13. This suggests that I am missing proper authentication and logging in through browser and creating a new board and playing on the new board would authenticate me properly somehow. 
14. How do I do the same in codes??