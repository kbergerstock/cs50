# Keith R. Bergerstock
# date :
# project:  flaskintro

from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('home.html')
    

if __name__ == '__main__':
    app.run(host = 'kbergerstock-ide50-4868566', port = 8080, debug = True)
   

    