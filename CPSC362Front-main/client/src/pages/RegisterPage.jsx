import React, { useState } from 'react';
import { Link } from 'react-router-dom';
import EtiquetteBG from '../images/Train.jpg';
import axios from 'axios';
import {
  MDBBtn,
  MDBContainer,
  MDBCard,
  MDBCardBody,
  MDBInput,
  MDBCheckbox
} from 'mdb-react-ui-kit';
import 'mdb-react-ui-kit/dist/css/mdb.min.css';

export default function RegisterPage() {
  const [username, setUsername] = useState('');
  const [name, setName] = useState('');
  const [email, setEmail] = useState('');
  const [phone_num, setPhoneNum] = useState('');
  const [password, setPassword] = useState('');
  const [repeatPassword, setRepeatPassword] = useState('');
  const [error, setError] = useState(null);
  const [serverError, setServerError] = useState(null);

  function validateEmail(email) {
    const re = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return re.test(email);
  }

  function validatePhone(phone) {
    const re = /^\d{10}$/;
    return re.test(phone);
  }

  function registerUser(ev) {
    ev.preventDefault();
    setError(null);
    setServerError(null);

    if (!username || !name || !email || !phone_num || !password || !repeatPassword) {
      setError('All fields are required.');
      return;
    }

    if (!validateEmail(email)) {
      setError('Invalid email format.');
      return;
    }

    if (!validatePhone(phone_num)) {
      setError('Invalid phone number format. Please enter a 10-digit number.');
      return;
    }

    if (password !== repeatPassword) {
      setError('Passwords do not match.');
      return;
    }

    axios.post('/api/create', {
      username,
      password,
      email,
      name,
      phone_num
    })
    .then(response => {
      console.log(response.data);
    })
    .catch(error => {
      if (error.response && error.response.data && error.response.data.error) {
        setServerError(error.response.data.error);
      } else {
        setServerError('An error occurred. Please try again.');
      }
      console.error(error);
    });
  }

  return (
    <MDBContainer fluid className='font-sans d-flex align-items-center justify-content-center bg-image' style={{ backgroundImage: `url(${EtiquetteBG})`, backgroundSize: 'cover', height: '100vh' }}>
      <div className='backdrop-blur-lg'></div>
      <MDBCard className='m-5 opacity-95' style={{ maxWidth: '600px' }}>
        <MDBCardBody className='px-5'>
          <h2 className="text-primary text-uppercase text-center mb-5">Create an account</h2>
          <form onSubmit={registerUser}>
            <MDBInput 
              wrapperClass='mb-4' 
              label='Username' 
              size='lg' 
              id='form0' 
              type='text' 
              value={username}
              onChange={ev => setUsername(ev.target.value)}
              required
            />
            <MDBInput 
              wrapperClass='mb-4' 
              label='Your Name' 
              size='lg' 
              id='form1' 
              type='text' 
              value={name}
              onChange={ev => setName(ev.target.value)}
              required
            />
            <MDBInput 
              wrapperClass='mb-4' 
              label='Your Email' 
              size='lg' 
              id='form2' 
              type='email' 
              value={email}
              onChange={ev => setEmail(ev.target.value)}
              required
            />
            <MDBInput 
              wrapperClass='mb-4' 
              label='Phone Number' 
              size='lg' 
              id='form5' 
              type='text' 
              value={phone_num}
              onChange={ev => setPhoneNum(ev.target.value)}
              required
            />
            <MDBInput 
              wrapperClass='mb-4' 
              label='Password' 
              size='lg' 
              id='form3' 
              type='password' 
              value={password}
              onChange={ev => setPassword(ev.target.value)}
              required
            />
            <MDBInput 
              wrapperClass='mb-4' 
              label='Repeat your password' 
              size='lg' 
              id='form4' 
              type='password' 
              value={repeatPassword}
              onChange={ev => setRepeatPassword(ev.target.value)}
              required
            />
            <div className='d-flex flex-row justify-content-center mb-4'>
              <MDBCheckbox name='flexCheck' id='flexCheckDefault' label='I agree to all statements in Terms of Service' />
            </div>
            {error && <p className="error text-danger">{error}</p>}
            {serverError && <p className="error text-danger">{serverError}</p>}
            <MDBBtn className='mb-4 w-100 bg-gradient-to-r from-green-500 to-cyan-400 transition duration-300 ease-in-out' size='lg' type='submit'>Register</MDBBtn>
            <div className="text-center py-2 text-gray-500">
              Already a member? <Link className="underline text" to={'/login'}>Login</Link>
            </div>
          </form>
        </MDBCardBody>
      </MDBCard>
    </MDBContainer>
  );
}
