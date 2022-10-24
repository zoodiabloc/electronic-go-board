`socat -d -d pty,raw,echo=0 pty,raw,echo=0`
> 2022/10/22 13:00:52 socat[3281] N PTY is /dev/pts/1
>
> 2022/10/22 13:00:52 socat[3281] N PTY is /dev/pts/2
>
> 2022/10/22 13:00:52 socat[3281] N starting data transfer loop with FDs [5,5] and [7,7]

In one terminal:
`cat < /dev/pts/1` 

In another terminal:
`echo "test" > /dev/pts/2`

Use the second virtual serial port in .env and use the echo command to the first virtual serial port.