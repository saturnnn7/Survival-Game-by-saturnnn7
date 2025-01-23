from ascii_magic import AsciiArt

my_art = AsciiArt.from_image('start/frame_07.png')
my_art.to_terminal(columns=100, monochrome=True)
my_art.to_html_file('cow_dalle.html', columns=100, monochrome=True)