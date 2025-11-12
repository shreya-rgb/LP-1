# pages/2_Health.py

import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt

# Retrieve values from session state
h = st.session_state.get("h")
w = st.session_state.get("w")

st.subheader("💡 BMI Calculator")
if h and w:
    bmi = w / ((h/100)**2)
    st.metric("Your BMI", f"{bmi:.2f}")
    if bmi < 18.5: st.warning("Underweight")
    elif bmi < 24.9: st.success("Healthy")
    elif bmi < 29.9: st.info("Overweight")
    else: st.error("Obese")

    # Create and display chart
    df = pd.DataFrame({"Category":["Under","Healthy","Over","You"], "Value":[18.5,24.9,29.9,bmi]})
    fig, ax = plt.subplots()
    ax.bar(df["Category"], df["Value"])
    ax.axhline(bmi, linestyle="--", color='red')
    ax.set_title("BMI Range Comparison")
    st.pyplot(fig)
else:
    st.info("Please enter valid Height and Weight in the sidebar on the Home page to see BMI.")