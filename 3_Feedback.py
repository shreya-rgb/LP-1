# pages/3_Feedback.py

import streamlit as st

st.subheader("📝 Feedback")
with st.form("f"):
    c = st.text_area("Comments")
    r = st.slider("Rate",1,5,3)
    if st.form_submit_button("Submit"):
        st.write("Thanks for your valuable feedback! 💗")
        st.write(f"Comment 🗨️: {c}")
        st.metric("Rating 🎚️", f"{r}/5")