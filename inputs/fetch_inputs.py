from pathlib import Path
from requests.utils import cookiejar_from_dict
import json
import requests

# login to aoc using the cookies, you need to copy the cookies as a json after looging in to aoc
# and paste them as a file under ./inputs/login_cookie.json
session = requests.session()
cookies = json.loads(Path("./inputs/login_cookie.json").read_text())
cookies = cookiejar_from_dict(cookies)
session.cookies.update(cookies)

#get every input using the login information an write them in to textfiles
for day in range(1,25):
    url = "https://adventofcode.com/2022/day/"+ str(day) +"/input"
    data = session.get(url).text
    file = open("./inputs/day_"+ str(day) +".txt", 'w')
    file.write(data)
    file.close()

    