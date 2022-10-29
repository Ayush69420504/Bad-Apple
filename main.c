#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
int main()
{
int x,y,i,j,avg,count,fps,t = 0;
clock_t begin,end;
double dt,ts;
struct winsize w;
ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
int H = w.ws_row, W = w.ws_col;
unsigned char frame[H][W][1];
memset(frame, 0, H*W*sizeof(char));
char path[100],ffmpeg[200];
char tframe[H*(15*W+1)];
memset(tframe, 0, H*(15*W+1)*sizeof(char));
char chars[10] = {' ', '.', ':', '!', '+', '*', 'e', '$', '@', '8'};
printf("Welcome to ascii video player\n");
printf("Dimensions: %dx%d\n", W, H);
printf("Path to file: ");
scanf("%s", &path);
if (access(path, F_OK) == -1)
{
printf("File does not exist\n");
return -1;
}
printf("FPS of video: ");
scanf("%d", &fps);
dt = 1.0/(double)fps;
j = sprintf(ffmpeg, "ffmpeg -loglevel panic -i %s -s %dx%d -vf \"fps=%d\" ", path, W, H, fps);
j += sprintf(ffmpeg+j, "-f image2pipe -vcodec rawvideo -pix_fmt rgb8 -");
printf("Starting ffmpeg child process: \"%s\"\n", ffmpeg);
printf("Press TAB+ENTER to continue\n");
printf("\e[?25l");
for (;;)
{
if (getchar() == '\t') break;
}
FILE *pipein = popen(ffmpeg, "r");
for (;;)
{
begin = clock();
count = fread(frame, 1, H*W, pipein);
if (count != H*W) break;
for (y = 0; y < H; y++)
{
for (x = 0; x < W; x++)
{
t += sprintf(tframe+t, "\033[38;5;%dm", frame[y][x][0]);
t += sprintf(tframe+t, "%c", chars[frame[y][x][0]*10/255]);
}
if (y != H - 1) t += sprintf(tframe+t, "\n");
}
printf("%s", tframe);
t = 0;
end = clock();
ts = (double)(end - begin) / CLOCKS_PER_SEC;
usleep((int)((dt - ts) * 1000000));
}
printf("\e[?25h");
printf("\033[0m");
fflush(pipein);
pclose(pipein);
return 0;
}
