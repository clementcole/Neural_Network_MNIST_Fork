import re
import requests
from lxml import html
from lxml.html.builder import E
import urllib2
from bs4 import BeautifulSoup

#CREATE A SESSION OBJECT
session_requests = requests.session()



#CREATE DICTIONARY FOR THE LOGIN INFORMATION
payload = {
	"username" :  "xxxxxxxx",
	"pass" :  "xxxxxxx",
	"csrfmiddlewaretoken": "xxxxxx"
}



#PERFORM THE LOGIN session
session_requests = requests.session() 
website = "https://bitbucket.org/account/signin/?next=/"
login_url = website
result = session_requests.get(login_url)



"""
Second, we would like to extract the csrf token from the web page, 
this token is used during login. For this example we are using lxml and xpath, 
we could have used regular expression or any other method that will extract this data.
"""
tree = html.fromstring(result.text)
authenticity_token = list(set(tree.xpath("//input[@name='csrfmiddlewaretoken']/@value")))[0]


"""
Next, we would like to perform the login phase. 
In this phase, we send a POST request to the login url. 
We use the payload that we created in the previous step as the data.
We also use a header for the request and add a referer key to it for the same url.
"""
result = session_requests.post(
	login_url, 
	data = payload, 
	headers = dict(referer=login_url)
)




"""
Now, that we were able to successfully login, 
we will perform the actual scraping from bitbucket dashboard page
"""
url = 'https://bitbucket.org/dashboard/projects'
result = session_requests.get(
	url, 
	headers = dict(referer = url)
)


"""
TESTING 
"""
print (result.content)
tree = html.fromstring(result.content)
bucket_names = tree.xpath("//div[@class='repo-list--repo']/a/text()")



"""
VALIDATE RESULTS
"""
result.ok # Will tell us if the last request was ok
result.status_code # Will give us the status from the last request



print(bucket_names)






formatted_html = "formatted.txt"
line_number = 0


def cleanhtml(raw_html):
  cleanr = re.compile('<.*?>')
  cleantext = re.sub(cleanr, '\t\t\t\t\n', raw_html)
  return cleantext


with open("raw_data.html", "r") as f:
	data = f.readlines()
	for line in data:
		
		fwrite = open(formatted_html, "a")
		fwrite.write(cleanhtml(line))

#print (cleanhtml("raw_data.html"))
