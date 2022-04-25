# Paul Kim, HW 9, Tuesday 7-8:50 PM Section, Spring 2022
# pbkim@usc.edu
# HW 9 - Music!

"""
Create a program which will scrape the site of two music venues and give you the schedule of shows

Requirements
- Make a local copy of the webpages (using urllib and Beautiful Soup)
- Put the HTML Pages in project directory in a subdirectory called sites/.
"""

# Imports
# pip3 install BeautifulSoup4
# For some reason, when running through module (not PyCharm) I get a No module named "bs4", however, code runs just fine in PyCharm.
from bs4 import BeautifulSoup as bs
import urllib.request
import ssl


# Code used to save webpages as a local copy
def store_webpage(url, ctx, fn):
    page = urllib.request.urlopen(url, context=ctx)
    soup = bs(page.read(), 'html.parser')
    f = open(fn, 'w')
    print(soup, file=f)
    f.close()


# Code used to load webpage
def load_webpage(url, ctx):
    page = urllib.request.urlopen(url, context=ctx)
    return bs(page.read(), 'html.parser')


# Main Function
def main():
    # Ignore SSL certificate errors
    ctx = ssl.create_default_context()
    ctx.check_hostname = False
    ctx.verify_mode = ssl.CERT_NONE

    # Code that saved a local copy of the webpages using urllib
    # url = 'https://www.blackcatdc.com/schedule.html'
    # url = 'https://www.lagreektheatre.com'
    # store_webpage(url, ctx, 'blackcatdc.html')
    # store_webpage(url, ctx, 'LA Greek Theatre.html')
    # *Note, the 930 website didn't work for me, so I just used some random site.

    # Accessing webpages locally
    blackcat = 'file:sites/blackcatdc.html'
    LAGreek = 'file:sites/LA Greek Theatre.html'
    soup = load_webpage(blackcat, ctx)
    soup2 = load_webpage(LAGreek, ctx)

    # Printing Formatted Data for Black Cat
    print('Concerts coming up at Black Cat:')
    Date1 = soup.find_all('div', class_='show')
    for date in Date1:
        if date.h2.text == "SHOW QUICK GUIDE":
            continue
        print("\t" + date.h2.text)
        print("\t\t" + date.h1.text)

    print()

    # Printing Formatted Data for Greek Theatre
    print("Concerts coming up at The Greek Theatre:")
    Date1 = soup2.find_all('div', class_='event-text')
    i = 0
    for date in Date1:
        # print("\t" + str(date.h4))
        print("\t" + soup2.select('div.desc span.m')[i].text + " " + soup2.select('div.desc span.d')[i].text +
              soup2.select('div.desc span.y')[i].text)
        print("\t\t" + date.h3.text)
        # print("\t\t" + date.h1.text)
        i += 1


if __name__ == '__main__':
    main()

# Passed All Checks
