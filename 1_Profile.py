# pages/1_Profile.py

import streamlit as st

# Retrieve values from session state
name = st.session_state.get("name")
age_n = st.session_state.get("age_n")
h = st.session_state.get("h")
w = st.session_state.get("w")

st.subheader("👤 Profile")
# st.markdown(f"**Name:** {name or '-'}")
st.markdown(f"Name: {name}")
st.markdown(f"**Age:** {int(age_n) if age_n else '-'}")
st.markdown(f"**Height:** {f'{h} cm' if h else '-'}")
st.markdown(f"**Weight:** {f'{w} kg' if w else '-'}")
if st.button("Motivate Me"): st.success(f"Keep going, {name or 'friend'}! 💪")