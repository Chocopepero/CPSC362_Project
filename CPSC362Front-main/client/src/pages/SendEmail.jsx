import React, { useEffect } from 'react';
import axios from 'axios';
import { useLocation, useNavigate } from 'react-router-dom';

export default function SendEmail() {
  const location = useLocation();
  const navigate = useNavigate();

  useEffect(() => {
    const { state } = location;

    if (state) {
      const { RoomType, date, searchPref, total } = state;

      const emailData = {
        roomType: RoomType,
        startDate: date[0].startDate,
        endDate: date[0].endDate,
        adults: searchPref.adult,
        children: searchPref.children,
        rooms: searchPref.room,
        total,
      };

      axios.post('/api/sendConfirmationEmail', emailData)
        .then(response => {
          console.log('Email sent successfully:', response.data);
          navigate('/confirmation'); // Redirect to a thank you page after sending email
        })
        .catch(error => {
          console.error('Error sending email:', error);
        });
    }
  }, [location, navigate]);

  return (
    <div className="flex items-center justify-center min-h-screen">
      <div className="text-center">
        <p>Sending confirmation email...</p>
      </div>
    </div>
  );
}
