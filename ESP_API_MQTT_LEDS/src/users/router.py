from fastapi import APIRouter, Depends
from users.schemas import NewUser, UserSaved
from users.models import User
from sqlalchemy.orm import Session
from datetime import datetime
from dependencies import get_db

router = APIRouter()


@router.get("/users")
async def get_users(db: Session = Depends(get_db)):
    try:
        users = db.query(User).all()
        return users
    except Exception as e:
        return e


@router.post("/create_user", response_model=UserSaved)
async def create_user(request: NewUser, db: Session = Depends(get_db)):
    data = User(name=request.name)
    try:
        db.add(data)
        db.commit()
        db.refresh(data)
        return data
    except Exception as e:
        return e