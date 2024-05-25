from fastapi import APIRouter, Depends
from leds.schemas import NewColors, ColorsSaved, NewLeds, LedsSaved, GetLeds, GetColors, Color
from leds.models import Colors, Leds
from typing import List
from sqlalchemy.orm import Session
from datetime import datetime
from dependencies import get_db

router = APIRouter()


@router.get("/all_colors")
async def get_colors(db: Session = Depends(get_db)):
    try:
        users = db.query(Colors).all()
        return users
    except Exception as e:
        return e


@router.post("/create_colors", response_model=ColorsSaved)
async def create_colors(request: NewColors, db: Session = Depends(get_db)):
    data = Colors(colors=request.colors)
    try:
        db.add(data)
        db.commit()
        db.refresh(data)
        return data
    except Exception as e:
        return e
    

@router.post("/all_leds")#, response_model=LedsSaved)
async def get_leds(request: GetLeds, db: Session = Depends(get_db)):
    try:
        leds = db.query(Leds).filter(Leds.user_id == request.user_id and Leds.device_id == request.device_id).all()
        data = []
        for led in leds:
             data.append(
                 {
                     'id': led.id,
                     'user_id': led.user_id,
                     'device_id': led.device_id,
                     'colors_id': led.colors_id
                 }
             )
        return leds
    except Exception as e:
        return e


@router.post("/create_leds", response_model=LedsSaved)
async def create_leds(request: NewLeds, db: Session = Depends(get_db)):
    data = Leds(user_id = request.user_id, device_id = request.device_id, colors_id = request.colors_id)
    try:
        db.add(data)
        db.commit()
        db.refresh(data)
        return data
    except Exception as e:
        return e


@router.post("/get_led", response_model=Color)
async def get_led(request: GetColors, db: Session = Depends(get_db)):
    try:
        color = db.query(Colors).filter(Colors.id == request.color_id).all()
        return {
            'color': color[0].colors
        }
    except Exception as e:
        return e
