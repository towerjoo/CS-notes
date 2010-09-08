#!/usr/bin/env python
#
# Copyright 2007 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#




import wsgiref.handlers


from google.appengine.ext import webapp
import os
from google.appengine.ext.webapp import template

from settings import *


class MainHandler(webapp.RequestHandler):

    def get(self):
        greetings = "welcome to here"
        url = "/docs/programming/index.html"
        url_linktext = "programming"
        template_values = {
          'greetings': greetings,
          'url': url,
          'url_linktext': url_linktext,
          }

        path = os.path.join(TEMPLATE_DIR, 'index.html')
        self.response.out.write(template.render(path, template_values))

def main():
    application = webapp.WSGIApplication([('/', MainHandler)],
                                       debug=DEBUG)
    wsgiref.handlers.CGIHandler().run(application)


if __name__ == '__main__':
  main()
