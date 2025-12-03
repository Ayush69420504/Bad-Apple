# Bad-Apple

This was my attempt at bad apple in everything, stupid project made by a stupider me from a stupidest time.
It uses ffmpeg to convert the video into a WxHx3 INT8 array, calls each frame converts to text, records the time elapsed,
prints frame, sleeps for 1/fps - computation+print_time, and goes onto the next frame.

If count!=WxH break, ensures that when data is empty, i.e video ends, the loop also ends.

At that time i had no idea how to use the actual libraries behind ffmpeg directly as sdk's, but now i could learn.

It worked surprisingly good, except for a bit of tearing at the edges of the terminal due to buffer overload probably.

Fin
