import React, { useState } from 'react';
import { Link } from 'react-router-dom';
import facebookLogo from './images/facebookLogo.png';
import instagramLogo from './images/instalogo.png';
import twitterLogo from './images/twitterlogo.png';
import Services from "./pages/Services.jsx";

export default function Footer() {
  const [email, setEmail] = useState('');
  const [errorMessage, setErrorMessage] = useState('');

  const handleSubmit = (e) => {
    e.preventDefault();
    const emailPattern = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    if (!emailPattern.test(email)) {
      setErrorMessage('Please enter a valid email address.');
      return;
    }
    setErrorMessage('');
    // Handle the form submission (e.g., send data to server)
    console.log('Email submitted:', email);
  };

  return (
    <div className="font-serif">
      <footer className="p-4 bg-gradient-to-t from-blue-500 to-[#afd3e2] text-white flex justify-between items-center">
        <div className="flex items-center space-x-4">
          <p className="font-bold">Follow us on Socials:</p>
          <img src={facebookLogo} alt="Facebook logo" className="w-10 h-10" />
          <img src={instagramLogo} alt="Instagram logo" className="w-10 h-10" />
          <img src={twitterLogo} alt="Twitter logo" className="w-10 h-10" />
        </div>

        <div className="flex flex-col items-center">
          <h2 className="font-bold mb-2">Subscribe for Promotions & News</h2>
          <form onSubmit={handleSubmit} className="flex flex-col items-center">
            <input
              type="email"
              id="email"
              name="email"
              required
              placeholder="Enter your email"
              className="p-2 mb-2 rounded"
              value={email}
              onChange={(e) => setEmail(e.target.value)}
            />
            {errorMessage && <p className="text-red-500">{errorMessage}</p>}
            <button type="submit" className="font-bold bg-white text-blue-500 p-2 rounded hover:bg-gray-200">Subscribe</button>
          </form>
        </div>

        <div className="flex flex-col space-y-5">
          <div>
            <Link to={Services} className="hover:underline">
                <p className="m-2 relative group">
                <span>About Us</span>
                <span className="absolute -bottom-1 left-1/2 w-0 h-2 bg-blue-600 group-hover:w-1/2 group-hover:transition-all"></span>
                <span className="absolute -bottom-1 right-1/2 w-0 h-2 bg-blue-600 group-hover:w-1/2 group-hover:transition-all"></span>
                </p>
            </Link>
          </div>
          <div>
            <Link to={Services} className="hover:underline">
                <p className="m-2 relative group">
                <span>Payment Policy</span>
                <span className="absolute -bottom-1 left-1/2 w-0 h-2 bg-blue-600 group-hover:w-1/2 group-hover:transition-all"></span>
                <span className="absolute -bottom-1 right-1/2 w-0 h-2 bg-blue-600 group-hover:w-1/2 group-hover:transition-all"></span>
                </p>
            </Link>
          </div>
        </div>
      </footer>
      <div className="bg-blue-600 flex justify-center">
        <div className="w-full max-w-screen-lg ml-0 mr-0 my-4">
          <p className="text-center text-white">Copyright Ⓒ {new Date().getFullYear()} The Blissful Hotel and Restaurant. All Rights Reserved</p>
        </div>
      </div>
    </div>
  );
}
