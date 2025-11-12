# Home.py

import streamlit as st, pandas as pd, matplotlib.pyplot as plt

# --- Shared Setup ---
st.set_page_config("Smart Health Dashboard", layout="centered")
st.title("Smart Health Dashboard")

# --- Shared Input Logic (These inputs will now appear on all pages) ---
name = st.sidebar.text_input("Name", placeholder="Enter name")
age = st.sidebar.text_input("Age", placeholder="Enter age (number)")
height_s = st.sidebar.text_input("Height (cm)", placeholder="e.g. 170")
weight_s = st.sidebar.text_input("Weight (kg)", placeholder="e.g. 60")

def to_num(s):
    try: return float(s)
    except: return None

age_n = to_num(age); h = to_num(height_s); w = to_num(weight_s)

# Store inputs in Streamlit's session state so all pages can access them
st.session_state["name"] = name
st.session_state["age_n"] = age_n
st.session_state["h"] = h
st.session_state["w"] = w

# --- Home Page Content ---
st.header("Welcome to the Dashboard! 👋")
st.write("Please select a page from the menu on the left to get started.")
st.caption("Your BMI tracker")