import pandas as pd
from sklearn.preprocessing import MultiLabelBinarizer, MinMaxScaler, OneHotEncoder
from sklearn.neighbors import KNeighborsClassifier
import numpy as np
import os

def load_model_and_data():
    base_dir = os.path.dirname(os.path.abspath(__file__))
    data_path = os.path.join(base_dir, 'data.csv')
    data = pd.read_csv(data_path)

    # Preprocessing
    data['skills'] = data['skills'].apply(lambda x: x.split(';'))
    mlb = MultiLabelBinarizer()
    skills_encoded = mlb.fit_transform(data['skills'])

    scaler = MinMaxScaler()
    experience_scaled = scaler.fit_transform(data[['experience']])

    ohe = OneHotEncoder(handle_unknown='ignore')
    category_encoded = ohe.fit_transform(data[['category']]).toarray()

    X = np.hstack([skills_encoded, experience_scaled, category_encoded])
    y = data['job_match']

    knn = KNeighborsClassifier(n_neighbors=3)
    knn.fit(X, y)

    return knn, mlb, scaler, ohe, data, y

def predict_job_match(knn, mlb, scaler, ohe, skills_input, experience_input, category_input, data, y):
    skills_input = [skill.strip() for skill in skills_input.split(',')]
    skills_vec = mlb.transform([skills_input])
    experience_vec = scaler.transform([[experience_input]])
    category_vec = ohe.transform([[category_input]]).toarray()
    X_input = np.hstack([skills_vec, experience_vec, category_vec])

    neighbors_idx = knn.kneighbors(X_input, n_neighbors=3, return_distance=False)[0]
    neighbors = y.iloc[neighbors_idx].tolist()
    return neighbors

if __name__ == "__main__":
    knn, mlb, scaler, ohe, data, y = load_model_and_data()
    skills = input("Enter skills (comma separated): ")
    experience = float(input("Enter years of experience: "))
    category = input("Enter job category: ")
    matches = predict_job_match(knn, mlb, scaler, ohe, skills, experience, category, data, y)
    print("Top 3 Suggested Job Matches:")
    for job in matches:
        print(f"- {job}")