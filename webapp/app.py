from flask import Flask, render_template, request, redirect, url_for, flash
import subprocess  # Used to run C code from Python
import os
from model_knn import load_model_and_data, predict_job_match

app = Flask(__name__)
app.secret_key = 'secret_key'
# Load AI model and preprocessors
knn, mlb, scaler, ohe, data, y = load_model_and_data()

# In-memory data storage
data_store = {'seekers': [], 'companies': []}

def save_input_file():
    with open('input.txt', 'w') as f:
        f.write(f"{len(data_store['seekers'])}\n")
        f.write(f"{len(data_store['companies'])}\n")
        for s in data_store['seekers']:
            f.write(s['name'] + '\n')
            f.write(str(len(s['skills'])) + '\n')
            for skill in s['skills']:
                f.write(skill + '\n')
        for c in data_store['companies']:
            f.write(c['name'] + '\n')
            f.write(str(len(c['skills'])) + '\n')
            for skill in c['skills']:
                f.write(skill + '\n')

@app.route('/')
def welcome():
    return render_template('welcome.html')

@app.route('/home')
def home():
    return render_template('home.html', seekers=data_store['seekers'], companies=data_store['companies'])

@app.route('/add_seeker', methods=['POST'])
def add_seeker():
    name = request.form['name']
    skills = [s.strip() for s in request.form['skills'].split(',')]
    experience = float(request.form['experience'])
    category = request.form['category']
    data_store['seekers'].append({'name': name, 'skills': skills, 'experience': experience, 'category': category})
    flash(f'Seeker {name} added.')
    return redirect(url_for('home'))

@app.route('/add_company', methods=['POST'])
def add_company():
    name = request.form['name']
    skills = [s.strip() for s in request.form['skills'].split(',')]
    data_store['companies'].append({'name': name, 'skills': skills})
    flash(f'Company {name} added.')
    return redirect(url_for('home'))

@app.route('/run_graph/<cmd>', methods=['GET'])
def run_graph(cmd):
    if not data_store['seekers'] or not data_store['companies']:
        flash('Please add job seekers and companies first.')
        return redirect(url_for('home'))

    save_input_file()
    exe_path = os.path.abspath(os.path.join('backend_c', 'jobmatching'))
    arg_map = {'dfs': 'dfs', 'bfs': 'bfs', 'match': 'match'}

    if cmd not in arg_map:
        flash('Invalid command.')
        return redirect(url_for('home'))

    args = [exe_path, 'input.txt', arg_map[cmd]]
    if cmd in ['dfs', 'bfs']:
        start_idx = request.args.get('start', '0')
        args.append(start_idx)

    try:
        result = subprocess.run(args, capture_output=True, text=True, check=True)
        output = result.stdout
    except Exception as e:
        flash(f'Error running graph algorithm: {e}')
        return redirect(url_for('home'))

    return render_template('results.html', output=output, algo=cmd.upper())

@app.route('/run_ai_recommend', methods=['POST'])
def run_ai_recommend():
    skills = request.form['skills']
    experience = float(request.form['experience'])
    category = request.form['category']
    matches = predict_job_match(knn, mlb, scaler, ohe, skills, experience, category, data, y)
    return render_template('results.html', output=None, job_matches=matches, algo='AI Recommendation')

if __name__ == '__main__':
    app.run(debug=True)