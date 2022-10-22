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

## How to run the application

`npm start`

## Project updates

### Append new moves is now working (2022.10.22)

The appending moves to a demo board has been tested and it works. Some sleep functions has been implemented to leave enough time for the server to properly authenticating users. 

To use and test the library's ability to append moves, run `npm start` to create a new demo board in a terminal (terminal 1) and to listen for responses from the socket connection.

Go to `indextest.js`. On line 24, modify the value of the reviewID variable to match the demo board ID shown in terminal 1. Also, on line 44, modify the second argument of the `await emitter.emitReviewAppendMove` function call. This argument is the string representation of the updated board state.

In a different termal (terminal 2), run `node indextest.js` to append the new move you define. Well it's more like setting the board to your defined state.

You should see that in both terminal 1 and terminal 2 there is a new event received from the server in our socket connection. The message should be `review/<reviewID>/r` and it should contain the new board state in the m field.

If you go to OGS to view the new demo board **https://online-go.com/demo/view/<reviewID>** or refresh the page if you're already there, you should see the board with the new state!

## Current steps to make appending moves works (2022.10.17)

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