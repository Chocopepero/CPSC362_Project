import React, { useState, useContext } from 'react';
import { Link, useNavigate } from 'react-router-dom';
import axios from 'axios';
import CheckInImg from '../images/checkin.jpg';
import BackgroundLogin from '../images/auroraScenic.jpg';
import {
  MDBBtn,
  MDBContainer,
  MDBCard,
  MDBCardBody,
  MDBCardImage,
  MDBRow,
  MDBCol,
  MDBInput,
  MDBCheckbox
} from 'mdb-react-ui-kit';
import 'mdb-react-ui-kit/dist/css/mdb.min.css';
import AuthContext from '../assets/components/Authenticate'; 

export default function LoginPage() {
    const [email, setEmail] = useState('');
    const [password, setPassword] = useState('');
    const [error, setError] = useState(null);
    const { login } = useContext(AuthContext); 
    const navigate = useNavigate();

    function validateEmail(email) {
        const re = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        return re.test(email);
    }

    function handleLogin(ev) {
        ev.preventDefault();
        setError(null); // Clear previous errors

        // Validate email format
        if (!validateEmail(email)) {
            setError('Invalid email format.');
            return;
        }

        // Send login request to backend
        axios.post('/api/login', {
            username: email, // Assuming username is the email
            password: password
        })
        .then(response => {
            console.log(response.data);
            if (response.status === 200) {
                const { name } = response.data;
                login({ email, name }); // Set the user session with name
                navigate('/'); 
            } else {
                setError('Login failed');
            }
        })
        .catch(error => {
            if (error.response) {
                if (error.response.status === 401) {
                    setError('Invalid username or password.');
                } else if (error.response.data && error.response.data.error) {
                    setError(error.response.data.error);
                } else {
                    setError('An error occurred. Please try again.');
                }
            } else if (error.request) {
                setError('Network error. Please check your internet connection.');
            } else {
                setError('An error occurred. Please try again.');
            }
            console.error(error);
        });
    }

    return (
        <MDBContainer fluid className='d-flex align-items-center justify-content-center bg-image' style={{ backgroundImage: `url(${BackgroundLogin})`, backgroundSize: 'cover', height: '100vh' }}>
            <MDBCard style={{ maxWidth: '600px' }}>
                <MDBRow className='g-0 d-flex align-items-center'>
                    <MDBCol md='4'>
                        <MDBCardImage src={CheckInImg} alt='phone' className='rounded-t-5 rounded-tr-lg-0' fluid />
                    </MDBCol>
                    <MDBCol md='8'>
                        <MDBCardBody>
                            <h1 className="text-4xl text-center mb-4">Login</h1>
                            <form onSubmit={handleLogin}>
                                <MDBInput 
                                    wrapperClass='mb-4' 
                                    label='Email address' 
                                    id='form1' 
                                    type='email'
                                    value={email}
                                    onChange={ev => setEmail(ev.target.value)}
                                    required
                                />
                                <MDBInput 
                                    wrapperClass='mb-4' 
                                    label='Password' 
                                    id='form2' 
                                    type='password'
                                    value={password}
                                    onChange={ev => setPassword(ev.target.value)}
                                    required
                                />
                                <div className="d-flex justify-content-between mx-4 mb-4">
                                    <MDBCheckbox name='flexCheck' value='' id='flexCheckDefault' label='Remember me' />
                                    <a href="#!">Forgot password?</a>
                                </div>
                                {error && <p className="error text-danger">{error}</p>}
                                <MDBBtn className="mb-4 w-100" type="submit">Sign in</MDBBtn>
                                <div className="text-center py-2 text-gray-500">
                                    Don't have an account yet?  
                                    <Link className="underline text" to={'/register'}>Register now</Link>
                                </div>
                            </form>
                        </MDBCardBody>
                    </MDBCol>
                </MDBRow>
            </MDBCard>
        </MDBContainer>
    );
}
