#include "maps.h"

static int get_colors(int fd, char ***floor, char ***ceiling, char *current_line);
static unsigned int rgb_to_uint(char ***rgb);
static int have_letters(char *color);
static int set_info(char letter, char *colors, char ****ceiling, char ****floor);

int colors(int fd, t_colors *colors, char *current_line)
{
    char **floor;
    char **ceiling;

    if(!get_colors(fd, &floor, &ceiling, current_line))
        return 0;
    colors->ceiling = rgb_to_uint(&ceiling);
    if(colors->ceiling == 0)
    {
        printf("error on ceiling color\n");
        return 0;
    }
    colors->floor = rgb_to_uint(&floor);
    if(colors->floor == 0)
    {
        printf("error on floor color\n");
        return 0;
    }
    return 1;
}

static int get_colors(int fd, char ***floor, char ***ceiling, char *current_line)
{
    char    **line_splitted_space;
    char    *colors;
    int     i;
    int     j;
    char    letter; 

    j = 0;
    while(j < 2)
    {
        colors = "\0";
        while(current_line[0] == '\n')
            current_line = get_next_line(fd);
        line_splitted_space = ft_split(current_line,' ');
        letter = line_splitted_space[0][0];
        i = 0;
        while(line_splitted_space[++i])
            colors = ft_strjoin(colors,line_splitted_space[i]);
        set_info(letter, colors, &floor, &ceiling);
        current_line = get_next_line(fd);
        free(colors);
        ++j;
    }
    return 1;
}

static unsigned int rgb_to_uint(char ***rgb)
{
    int red;
    int green;
    int blue;

    red = ft_atoi((*rgb)[0]);
    if(red < 0 || red > 255 || have_letters((*rgb)[0]))
        return 0;
    green = ft_atoi((*rgb)[1]);
    if(green < 0 || green > 255 || have_letters((*rgb)[1]))
        return 0;
    blue = ft_atoi((*rgb)[2]);
    if((*rgb)[2][ft_strlen((*rgb)[2]) - 1] == '\n')
        (*rgb)[2][ft_strlen((*rgb)[2]) - 1] = '\0';
    if(blue < 0 || blue > 255 || have_letters((*rgb)[2]))
        return 0;
    return ((red << 16) + (green << 8) + blue);
}

static int have_letters(char *color)
{
    int i;

    i = 0;
    while(color[i])
    {
        if(!ft_isdigit(color[i]))
            return 1;
        ++i;
    }
    return 0;
}

static int set_info(char letter, char *colors, char ****ceiling, char ****floor)
{

    if(letter == 'f' || letter == 'F')
        (**floor) =  ft_split(colors,',');
    else if(letter == 'c' || letter == 'C')
        (**ceiling) = ft_split(colors,',');
    else
        return 0;
    return 1;
}