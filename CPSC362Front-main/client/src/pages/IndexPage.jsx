import React, { useState, useRef, useEffect } from "react";
import { Link, useNavigate } from 'react-router-dom';
import img1 from "../images/Hotelpic1.jpeg";
import img2 from "../images/DeluxeRoom.webp";
import img3 from "../images/Hotelpic3.webp";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faCalendarDays } from "@fortawesome/free-regular-svg-icons";
import { faBed, faPerson } from "@fortawesome/free-solid-svg-icons";
import { DateRange } from "react-date-range";
import { format } from "date-fns";
import "react-date-range/dist/styles.css"; // main css file
import "react-date-range/dist/theme/default.css"; // theme css file
import Select from 'react-select';

export default function IndexPage() {
    // room data
    const rooms = [
        {
            id: 1,
            name: 'Deluxe Room',
            description: 'A spacious room with a beautiful view of the city.',
            price: '$200 per night',
            imageUrl: img2,
            link: '/DeluxeRoom'
        },
        {
            id: 2,
            name: 'Standard Room',
            description: 'A comfortable room with all the basic amenities.',
            price: '$100 per night',
            imageUrl: img1,
            link: '/StandardRoom'
        },
        {
            id: 3,
            name: 'Suite',
            description: 'A luxurious suite with a separate living area.',
            price: '$300 per night',
            imageUrl: img3,
            link: '/SuiteRoom'
        }
    ];

    const options = rooms.map(room => ({
        value: room.id,
        label: room.name,
    }));

    const [RoomType, setRoomType] = useState("");
    const [openDate, setOpenDate] = useState(false);
    const [date, setDate] = useState([
        {
            startDate: new Date(),
            endDate: new Date(),
            key: "selection",
        },
    ]);
    const [openOptions, setOpenOptions] = useState(false);
    const [searchPref, setPreferenceSearch] = useState({
        adult: 1,
        children: 0,
        room: 1,
    });

    const navigate = useNavigate();
    
    const dateRangeRef = useRef(null);
    const optionsRef = useRef(null);

    const handleOption = (name, operation) => {
        setPreferenceSearch((prev) => {
            return {
                ...prev,
                [name]: operation === "i" ? searchPref[name] + 1 : searchPref[name] - 1,
            };
        });
    };

    const handleSearch = () => {
        navigate("/confirmation", { state: { RoomType, date, searchPref } });
    };

    const handleClickOutside = (event) => {
        if (dateRangeRef.current && !dateRangeRef.current.contains(event.target)) {
            setOpenDate(false);
        }
        if (optionsRef.current && !optionsRef.current.contains(event.target)) {
            setOpenOptions(false);
        }
    };

    useEffect(() => {
        document.addEventListener('mousedown', handleClickOutside);
        return () => {
            document.removeEventListener('mousedown', handleClickOutside);
        };
    }, []);

    return (
        <div className="p-4 flex-col">
            <div className="justify-between">
                <div className="container h-16 bg-[white] border-[3px] border-[solid]
                border-x-blue-700 border-y-blue-400 flex items-center justify-between 
                px-0 py-[10px] mx-auto rounded-2xl  -bottom-[25px] w-full max-w-screen-lg">
                    <div className="flex items-center gap-[10px] text-xs">
                        <FontAwesomeIcon icon={faBed} className="text-[lightgray] pl-2" />
                        <Select
                            options={options}
                            onChange={(selectedOption) => setRoomType(selectedOption ? selectedOption.label : "")}
                            isSearchable
                            isClearable
                            placeholder="Pick a room :)"
                            classNamePrefix="react-select"
                            className="w-48"
                        />
                    </div>
                    <div className="flex items-center gap-[10px]">
                        <FontAwesomeIcon icon={faCalendarDays} className="text-[lightgray]" />
                        <span
                            onClick={() => setOpenDate(!openDate)}
                            className=" text-[lightgray] cursor-pointer"
                        >{`${format(date[0].startDate, "MM/dd/yyyy")} to ${format(date[0].endDate, "MM/dd/yyyy")}`}</span>
                        {openDate && (
                            <div ref={dateRangeRef} className="absolute top-40 z-40">
                                <DateRange
                                    editableDateInputs={true}
                                    onChange={(item) => setDate([item.selection])}
                                    moveRangeOnFirstSelection={false}
                                    ranges={date}
                                    className="date"
                                    minDate={new Date()}
                                />
                            </div>
                        )}
                    </div>
                    <div className="flex items-center gap-[10px]">
                        <FontAwesomeIcon icon={faPerson} className="text-[lightgray]" />
                        <span
                            onClick={() => setOpenOptions(!openOptions)}
                            className="text-[lightgray] cursor-pointer"
                        >{`${searchPref.adult} adult · ${searchPref.children} children · ${searchPref.room} room`}</span>
                        {openOptions && (
                            <div ref={optionsRef} className="absolute top-40 z-40 bg-[white] text-[gray] 
                            rounded-[5px] [box-shadow:0px_0px_10px_-5px_rgba(0,_0,_0,_0.4)]">
                                <div className="w-[200px] flex justify-between m-[10px]">
                                    <span className="optionText">Adult</span>
                                    <div className="flex items-center gap-[10px] text-[12px] text-[black]">
                                        <button
                                            disabled={searchPref.adult <= 1}
                                            className="w-[30px] h-[30px] border-[1px] border-[solid]
                                             border-[#0071c2] text-[#0071c2]
                                             shadow-lg rounded-b-md cursor-pointer bg-[white]"
                                            onClick={() => handleOption("adult", "d")}
                                        >
                                            -
                                        </button>
                                        <span className="optionCounterNumber">{searchPref.adult}</span>
                                        <button
                                            className="w-[30px] h-[30px] border-[1px] border-[solid]
                                            border-[#0071c2] text-[#0071c2]
                                            shadow-lg rounded-t-md cursor-pointer bg-[white]"
                                            onClick={() => handleOption("adult", "i")}
                                        >
                                            +
                                        </button>
                                    </div>
                                </div>
                                <div className="w-[200px] flex justify-between m-[10px]">
                                    <span className="optionText">Children</span>
                                    <div className="flex items-center gap-[10px] text-[12px] text-[black]">
                                        <button
                                            disabled={searchPref.children <= 0}
                                            className="w-[30px] h-[30px] border-[1px] border-[solid]
                                             border-[#0071c2] text-[#0071c2]
                                             shadow-lg rounded-b-md cursor-pointer bg-[white]"
                                            onClick={() => handleOption("children", "d")}
                                        >
                                            -
                                        </button>
                                        <span className="optionCounterNumber">{searchPref.children}</span>
                                        <button
                                            className="w-[30px] h-[30px] border-[1px] border-[solid]
                                            border-[#0071c2] text-[#0071c2]
                                            shadow-lg rounded-t-md cursor-pointer bg-[white]"
                                            onClick={() => handleOption("children", "i")}
                                        >
                                            +
                                        </button>
                                    </div>
                                </div>
                                <div className="w-[200px] flex justify-between m-[10px]">
                                    <span className="optionText">Room</span>
                                    <div className="flex items-center gap-[10px] text-[12px] text-[black]">
                                        <button
                                            disabled={searchPref.room <= 1}
                                            className="w-[30px] h-[30px] border-[1px] border-[solid]
                                             border-[#0071c2] text-[#0071c2]
                                             shadow-lg rounded-b-md cursor-pointer bg-[white]"
                                        >
                                            -
                                        </button>
                                        <span className="optionCounterNumber">{searchPref.room}</span>
                                        <button
                                            className="w-[30px] h-[30px] border-[1px] border-[solid]
                                            border-[#0071c2] text-[#0071c2]
                                            shadow-lg rounded-t-md cursor-pointer bg-[white]"
                                            onClick={() => handleOption("room", "i")}
                                        >
                                            +
                                        </button>
                                    </div>
                                </div>
                            </div>
                        )}
                    </div>
                    <div className="flex items-center gap-[10px] pr-2">
                        <button className="bg-[#1aa7ec] text-white py-[10px] 
                        px-5 border-white cursor-pointer hover:bg-cyan-700 rounded-full" onClick={handleSearch}>
                            Reserve Room
                        </button>
                    </div>
                </div>
            </div>

            <div className="container m-auto p-8">
                <h1 className="text-4xl font-bold mb-4 px-20">Welcome, Guest</h1>
                <p className="text-lg mb-8 px-20">Enjoy your luxurious stay and peaceful getaway at the Blissful Hotel</p>

                <h2 className="text-3xl font-bold justify-between mb-4 px-20">Our Rooms</h2>
                <div className="w-full px-4 md:px-8 lg:px-16">
                    <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-12 justify-items-stretch">
                        {rooms.map(room => (
                            <div key={room.id} className="border rounded-lg overflow-hidden shadow-lg transform transition-transform hover:scale-105">
                                <img src={room.imageUrl} alt={room.name} className="w-full h-48 object-cover" />
                                <div className="p-4">
                                    <h3 className="text-xl font-bold">{room.name}</h3>
                                    <p className="mt-2 text-gray-600">{room.description}</p>
                                    <p className="mt-2 font-bold">{room.price}</p>
                                    <Link to={room.link} className="mt-4 inline-block bg-blue-500 text-white py-2 px-4 rounded">
                                        View More
                                    </Link>
                                </div>
                            </div>
                        ))}
                    </div>
                </div>
            </div>
        </div>
    );
}
